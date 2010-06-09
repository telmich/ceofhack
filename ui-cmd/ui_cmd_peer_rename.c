/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Rename peer
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
   char oldnick[EOF_L_NICKNAME+1];
   char newnick[EOF_L_NICKNAME+1];
   char errmsg[EOF_L_MESSAGE+1];
   char id[EOF_L_ID+1];
   int sockfd;

   /* terminate, so there is at least one \0 */
   memset(oldnick, 0, EOF_L_NICKNAME+1);
   memset(newnick, 0, EOF_L_NICKNAME+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);
   memset(id, 0, EOF_L_ID+1);

   if(argc != 3) {
      printf("%s: <oldnick> <newnick>\n", argv[0]);
      return 1;
   }
   strncpy(oldnick, argv[1], EOF_L_NICKNAME);
   strncpy(newnick, argv[2], EOF_L_NICKNAME);

   if((sockfd = eof_ui_init(id)) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   /* peer add */
   printf("Renaming peer %s->%s\n", oldnick, newnick);
   if(!eof_ui_peer_rename(sockfd, errmsg, oldnick, newnick)) {
      if(errno) {
         perror("eof_ui_peer_rename");
      } else {
         printf("/peer rename EOFi error: %s\n", errmsg);
      }
   }

   /* deregister */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
