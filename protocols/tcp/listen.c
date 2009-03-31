/* "Briefkasten". Author: apic
 * Coding style: See /usr/src/linux/Documentation/CodingStyle :-P
 */

#include <sys/types.h>  
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdint.h>

int tcp_listen(const char *host, const char *serv)
{
	int listenfd, n;
	const int on = 1;
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
         	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(n));
         	exit(3);
         }
	ressave = res;

	do {
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (listenfd < 0)
			continue;		/* error, try next one */

		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;			/* success */

		close(listenfd);	/* bind error, close and try next one */
	} while ( (res = res->ai_next) != NULL);

	if (res == 0) {
		perror("socket or bind");
		exit(4);
	}

	listen(listenfd, 1024);

	freeaddrinfo(ressave);

	return(listenfd);
}

ssize_t write_all(int fd, const void *buf, size_t count)
{
	size_t written=0;
	while(written < count) {
		ssize_t n = write(fd, buf+written, count-written);
		if(n<0 && errno == EINTR)
			continue;
		if(n<=0)
			return n;
		written += n;
	}
	return written;
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_storage cliaddr;

	if(argc != 2) {
		fprintf(stderr, "No URL.\n");
		exit(1);
	}

	if(memcmp(argv[1], "tcp:", strlen("tcp:"))) {
		fprintf(stderr, "Invalid protocol.\n");
		exit(2);
	}

	char *addr = argv[1] + strlen("tcp:");
	while(*addr == '/')
		addr++;

	char *port = addr;
	while(*port && *port != ':')
		port++;
	if(*port == ':') {
		*port = 0;
		++port;
	}

	listenfd = tcp_listen(addr, *port ? port : "4242");

	for (;;) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
		if(connfd >= 0) {
			ssize_t n, siz = 0;
			char c = '0';
			do {
				if(c < '0' || c > '9')
					break;
					
				siz *= 10;
				siz += c-'0';
				if(siz < 0) //overflow
					break;
				do {
					n = read(connfd, &c, 1);
				} while (n < 0 && errno == EINTR);
			} while(n == 1);

			if(c != '\n' || siz < 0 || siz > 65536) {  //64k ought to be enough for anybody [tm]
				close(connfd);
				continue;
			}

			char buf[siz];
			size_t got=0;
			while(got<siz) {
				n = read(connfd, buf, siz-got);
				if(n < 0 && errno == EINTR)
					continue;
				if(n <= 0)
					break;
				got += n;
			}
			close(connfd);
			
			int sizlen = snprintf(0, 0, "%zd\n", siz);
			char sizbuf[sizlen+1];
			snprintf(sizbuf, sizlen+1, "%zd\n", siz);
			write_all(1, "2002", 4);
			write_all(1, sizbuf, sizlen);
			write_all(1, buf, siz);
		}
	}
}

