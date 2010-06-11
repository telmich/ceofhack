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
 * Show peer
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
   char keyid[EOF_L_KEYID+1];
   char errmsg[EOF_L_MESSAGE+1];
   char id[EOF_L_ID+1];
   char *addr;
   int sockfd, noa, i;

   /* terminate, so there is at least one \0 */
   memset(nick, 0, EOF_L_NICKNAME+1);
   memset(keyid, 0, EOF_L_KEYID+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);
   memset(id, 0, EOF_L_ID+1);

   if(argc != 2) {
      printf("%s: <nick>\n", argv[0]);
      return 1;
   }
   strncpy(nick, argv[1], EOF_L_NICKNAME);

   if((sockfd = eof_ui_init(id)) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   /* peer show */
   if((noa = eof_ui_peer_show(sockfd, errmsg, nick, keyid, &addr)) == -1) {
      if(errno) {
         perror("eof_ui_peer_show");
      } else {
         printf("/peer add EOFi error: %s\n", errmsg);
      }
      return 1;
   }

   printf("Peer %s (%s) %d:", nick, keyid, noa);

   for(i=0; i<noa; i++) {
      printf(" %s", addr + (EOF_L_NICKNAME+1)*i);
   }
   printf("\n");

   /* deregister */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
