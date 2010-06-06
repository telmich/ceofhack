/*******************************************************************************
 *
 * 2010    Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * List peers
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
   char id[EOF_L_ID+1];
   char errmsg[EOF_L_MESSAGE+1];

   int sockfd;

   int nop, i;
   char *peers;
   
   memset(id, 0, EOF_L_ID+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);

   if((sockfd = eof_ui_init(id)) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   if((nop = eof_ui_peer_list(sockfd, errmsg, &peers)) == -1) return 1;

   printf("Number of peers: %d\n", nop);

   for(i=0; i < nop; i++ ) {
      printf("Peer %d: %s\n", i, peers + (i * (EOF_L_NICKNAME+1)));
   }

   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
