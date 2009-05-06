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
 * tcp listener
 *
 */

#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  /* htons       */
#include <sys/poll.h>   /* poll        */
#include <stdio.h>      /* perror()    */


#include "eof.h"   /* EOF */

#define WE "tcp/c3/ltp:"
#define SOCK_QUEUE   32          /* maximum elements in queue */

int main()
{
   char input[EOF_L_PKG_MAX+1];
   char address[EOF_L_ADDRESS+1];
   char *p1, *p2;
   int tmp, sock;
   int16_t port;
   ssize_t len;
   struct sockaddr_in ins;

   /* read init sequence: 1001 */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, WE "cmd %s\n", input);
   
   /* read the url */
   read(STDIN_FILENO, input, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, WE "ignoring url %s\n", input);

   /* get address and port */
   p1 = strchr(input, ':');
   if(!p1) {
      fprintf(stderr, WE "bad url %s\n", input);
      return 1;
   }
   ++p1;

   p2 = strchr(p1, ':');
   if(!p2) {
      fprintf(stderr, WE "port missing in %s\n", input);
      return 1;
   }

   len = p2 - p1;
   strncpy(address, p1, len);
   address[len] = '\0';
   fprintf(stderr, WE "addr=%s\n", address);

   port = strtol(p2+1, NULL, 10);
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

   /* read commands, socket and children */
   while(1) {
      len = read(STDIN_FILENO, input, EOF_L_PKG_MAX+1);
      if(len < 0) {
         perror("tp/dummy/listen: read");
         return 1;
      }

      if(len > EOF_L_PKG_MAX) {
         fprintf(stderr, "Packet too big (%lu)!\n", len);
         continue;
      }
      input[len] = '\0';
      fprintf(stderr, "dummy-LTP received command: %s (until first \\0)\n", input);

      if(!strncmp(input, EOF_CMD_TPL_STOP, EOF_L_CMD)) {
         fprintf(stderr, "dummy/c: Time to say goodbye...\n");
         return 0;
      }
   }

   return 0;
}
