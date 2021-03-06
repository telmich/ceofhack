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
 * The sample user interface -- send a message
 *
 */

#include <limits.h>     /* PATH_MAX          */
#include <stdio.h>      /* printf()          */
#include <string.h>     /* strncpy()         */
#include <errno.h>      /*                   */
#include <stdlib.h>     /* free()            */

#include <eof.h>        /* functions etc.    */

int main(int argc, char *argv[])
{
   char nick[EOF_L_NICKNAME+1];
   char msgtxt[EOF_L_MESSAGE+1];
   char errmsg[EOF_L_MESSAGE+1];
   char id[EOF_L_ID+1];
   int sockfd;

   /* terminate, so there is at least one \0 */
   nick[EOF_L_NICKNAME] = 0;
   msgtxt[EOF_L_MESSAGE] = 0;
   errmsg[EOF_L_MESSAGE] = 0;
   id[EOF_L_ID] = 0;

   if(argc != 3) {
      printf("%s: <nick> <msg>\n", argv[0]);
      return 1;
   }
   strncpy(nick, argv[1], EOF_L_NICKNAME);
   strncpy(msgtxt, argv[2], EOF_L_MESSAGE);

   if((sockfd = eof_ui_init(id)) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   /* peer send */
   printf("Sending message to %s\n", nick);
   if(!eof_ui_peer_send(sockfd, errmsg, nick, msgtxt)) {
      if(errno) {
         perror("eof_ui_peer_send");
      } else {
         printf("/peer send EOFi error: %s\n", errmsg);
      }
      return 1;
   }

   /* deregister */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
