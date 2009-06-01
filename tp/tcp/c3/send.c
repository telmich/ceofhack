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
   char *p1;
   int tmp, sock;
   int16_t port;
   struct sockaddr_in ins;
   struct pollfd plist[2];

   memset(input, 0, EOF_L_PKG_MAX+1);

   /* read init sequence: 1000 */
   read_all(STDIN_FILENO, input, EOF_L_CMD);
   fprintf(stderr, WE "cmd %s\n", input);
   if(strncmp(input, EOF_CMD_TPS, EOF_L_CMD)) {
      fprintf(stderr, WE "wrong cmd: %s\n", input);
      return 0;
   }
   
   /* read the url */
   read_all(STDIN_FILENO, addr, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, WE "using url %s\n", input);

   /* find beginning of port */
   p1 = strchr(input, ':');
   if(!p1) {
      fprintf(stderr, WE "bad url %s\n", input);
      return 1;
   }

   tmp = p1 - input;
   strncpy(address, input, tmp);
   address[tmp] = '\0';
   fprintf(stderr, WE "addr=%s\n", address);

   port = strtol(p1+1, NULL, 10);
   fprintf(stderr, WE "port=%d\n", port);


   /* listen to it */
   memset(&ins, 0, sizeof(ins));
   ins.sin_family = AF_INET;
   ins.sin_port   = htons(port);
   if(!inet_aton(address, &(ins.sin_addr) ) ) {
      write(2,"broken ipn\n",11);
      return 0;
   }

   sock = socket(PF_INET, SOCK_STREAM, 0);
   if(sock == -1 ) {
      perror("socket");
      return 0;
   }

   tmp = 1;
   // lose the pesky "Address already in use" error message
   if(setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) == -1) {
      perror("setsockopt");
      return 0;
    }

   if(bind(sock,(struct sockaddr *)&ins,sizeof(ins)) == -1) {
      perror("bind");
      return 0;
   }

   /* start listening */
   if(listen(sock, SOCK_QUEUE) == -1) {
      perror("listen");
      return 0;
   }

   /* read commands from EOFi and data from socket and children */
   while(1) {
      memset(&plist, 0, sizeof(plist));
      plist[0].fd       = STDIN_FILENO;
      plist[0].events   = POLLIN | POLLPRI;
      plist[1].fd       = sock;
      plist[1].events   = POLLIN | POLLPRI;

      if(poll(&plist[0], 2, -1) != -1) {
         if(plist[0].revents & (POLLIN | POLLPRI)) {
            tmp = eofi_ltp_read(plist[0].fd, &input[0]);
         }

         if(plist[1].revents & (POLLIN | POLLPRI)) {
            tmp = read_socket(plist[1].fd, &input[0]);
            fprintf(stderr, WE "read-socket: %d\n", tmp);
            if(tmp == -1) {
               perror("read_socket");
               continue;
            }
            eof_ltp_write(input, tmp);
         }

         if(tmp == -1) {
            fprintf(stderr, WE "input read error\n");
            continue;
         }
            
         input[tmp] = '\0';

         fprintf(stderr, WE "input=%s\n", input);
      } else {
         perror(WE "poll");
      }
   }

   return 0;
}
