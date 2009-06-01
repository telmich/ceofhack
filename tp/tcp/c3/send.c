/*******************************************************************************
 *
 * 2008      Nico Schottelius (nico-ceofhack at schottelius.org)
 *
 * This file is part of ceofhack.

 * ceofhack is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ceofhack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ceofhack.  If not, see <http://www.gnu.org/licenses/>.

 *
 * tcp sender
 *
 */

#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>  /* htons       */
#include <sys/poll.h>   /* poll        */
#include <stdio.h>      /* perror()    */
#include <errno.h>         /* errno    */
#include <sys/socket.h>    /* accept   */


#include "eof.h"        /* EOF */
#include "ceofhack.h"   /* read_all */
#include "shcl.h"       /* use helpers */

#define WE "tcp/c3/tp:"

/* 
 * FIXME: mid term: create somethink usable for all TP
 * maybe using some kind of union structure
 * FIXME: long term: create libEOFs
 */

int main()
{
   char input[EOF_L_PKG_MAX+1];
   char addr[EOF_L_ADDRESS+1];
   char size[EOF_L_SIZE+1];
   char *p, *host;
   int sock;
   int16_t port;
   struct sockaddr_in ins;
   ssize_t len, len2;

   memset(input, 0, EOF_L_PKG_MAX+1);
   memset(addr, 0, EOF_L_ADDRESS+1);
   memset(size, 0, EOF_L_SIZE+1);

   /* read init sequence: 1000 */
   read_all(STDIN_FILENO, input, EOF_L_CMD);
   fprintf(stderr, WE "cmd %s\n", input);
   if(strncmp(input, EOF_CMD_TPS, EOF_L_CMD)) {
      fprintf(stderr, WE "wrong cmd: %s\n", input);
      return 1;
   }
   
   /* read the url */
   read_all(STDIN_FILENO, addr, EOF_L_ADDRESS);
   fprintf(stderr, WE "using url %s\n", addr);

   /* find host */
   host = strchr(addr, ':');
   if(!host) {
      fprintf(stderr, WE "bad url %s\n", addr);
      return 1;
   }

   host++;

   p = strchr(host, ':');
   if(!p) {
      fprintf(stderr, WE "bad url %s\n", addr);
      return 1;
   }
   *p = 0;
   p++;

   fprintf(stderr, WE "host=%s\n", host);

   port = strtol(p, NULL, 10);
   fprintf(stderr, WE "port=%d\n", port);

   /* get size */
   read_all(STDIN_FILENO, size, EOF_L_SIZE);
   len = strtoul(size, NULL, 10);
   fprintf(stderr, WE "pkglen=%ld (%s)\n", (long) len, size);

   /* get message */
   if((len2 = read_all(STDIN_FILENO, input, len)) != len) {
      fprintf(stderr, WE "read len (%ld) != len (%ld)\n", (long) len2, (long) len);
      return 0;
   }

   /* connect to it */
   memset(&ins, 0, sizeof(ins));
   ins.sin_family = AF_INET;
   ins.sin_port   = htons(port);
   if(!inet_aton(host, &(ins.sin_addr) ) ) {
      fprintf(stderr, WE "broken host/ipn\n");
      return 0;
   }
   sock = socket(PF_INET, SOCK_STREAM, 0);
   if(sock == -1 ) {
      perror(WE "socket");
      return 0;
   }

   if(connect(sock,(struct sockaddr *)&ins,sizeof(ins)) == -1) {
      perror(WE "connect");
      return 0;
   }

   if(write_all(sock, input, len) != len) {
      perror(WE "send message");
      return 0;
   }

   return 1;
}
