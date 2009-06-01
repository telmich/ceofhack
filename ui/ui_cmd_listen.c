/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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

#include "eof.h"        /* functions etc.    */
#include "shcl.h"       /* simple helper     */

int main()
{
   char nick[EOF_L_NICKNAME+1];
   char msgtxt[EOF_L_MESSAGE+1];
   char cmd[EOF_L_CMD+1];
   struct pollfd  pfd;
   int sockfd, cnt;


   if((sockfd = eof_ui_connect()) == -1) {
      perror("eof_ui_connect");
      return 1;
   }

   if(!eof_ui_register(sockfd)) {
      perror("eof_ui_register");
      return 1;
   }

   /* terminate, so there is at least one \0 */
   cmd[EOF_L_CMD] = 0;
   nick[EOF_L_NICKNAME] = 0;
   msgtxt[EOF_L_MESSAGE] = 0;

   while(1) {
      pfd.fd = sockfd;
      pfd.events = POLLIN | POLLPRI;
      pfd.revents = 0;

      memset(cmd, 0, EOF_L_CMD+1);
      memset(nick, 0, EOF_L_NICKNAME+1);
      memset(msgtxt, 0, EOF_L_MESSAGE+1);

      cnt = poll(&pfd, 1, -1);
      if(cnt == -1) {
         if(errno != EINTR) {
            perror("poll");
            return 1;
         }   
      } else { /* EOFi packet coming in */
         if(read_all(sockfd, cmd, EOF_L_CMD) != EOF_L_CMD) {
            printf("no EOFi command...dying\n");
            return 1;
         }
         if(strncmp(cmd, EOF_CMD_UI_MSGRECEIVED, EOF_L_CMD)) {
            printf("Unhandled cmd: %s\n", cmd);
            return 1;
         }

         if(!eof_va_read(sockfd, 2, EOF_L_NICKNAME, nick, EOF_L_MESSAGE, msgtxt)) {
            perror("!eof_va_read");
            return 1;
         }

         printf("<%s> %s\n", nick, msgtxt);
      }   
   }   

   /* FIXME: deregister on ctrl-c */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}