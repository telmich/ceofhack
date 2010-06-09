/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * User interface that only listens for messages
 *
 */

#include <poll.h>       /* guess what        */
#include <stdio.h>      /* printf()          */
#include <string.h>     /* strncpy()         */
#include <errno.h>      /*                   */
#include <stdlib.h>     /* free()            */
#include <unistd.h>     /* read              */

#include <eof.h>        /* functions etc.    */
#include "shcl.h"       /* simple helper     */

int main()
{
   char data[EOF_L_PKG_MAX+1];
   char id[EOF_L_ID+1];
   struct pollfd  pfd;
   int sockfd, cnt;
   ssize_t bread;

   /* terminate, so there is at least one \0 */
   id[EOF_L_ID] = 0;

   if((sockfd = eof_ui_init(id)) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   while(1) {
      pfd.fd = sockfd;
      pfd.events = POLLIN | POLLPRI;
      pfd.revents = 0;

      memset(id, 0, EOF_L_ID+1);
      memset(data, 0, EOF_L_PKG_MAX+1);

      cnt = poll(&pfd, 1, -1);
      if(cnt == -1) {
         if(errno != EINTR) {
            perror("poll");
            return 1;
         }
      }
      if(pfd.revents & POLLHUP) {
         printf("ceof vanished, exiting.\n");
         return 0;
      }

      /* EOFi packet coming in */
      bread = read(sockfd, data, EOF_L_PKG_MAX);
      if(bread == -1) {
         if(errno != EINTR) {
            perror("read");
            return 1;
         } else {
            continue;
         }
      }

      data[bread] = 0;

      printf("%s\n", data);
   }   

   /* will never be called, because ctrl-c exits us */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
