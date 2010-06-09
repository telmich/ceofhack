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
 * UI->EOFi: Send message to peer
 *
 */

#include <stdio.h>      /* perror()          */
#include <string.h>     /* strncmp()         */
#include <stdlib.h>     /* strtoul, calloc   */
#include <errno.h>      /*                   */

#include <eof.h>        /* defines            */
#include "shcl.h"       /* functions etc.     */

int eof_ui_peer_rename(int sockfd, char errmsg[EOF_L_MESSAGE],
                     char oldnick[EOF_L_NICKNAME], char newnick[EOF_L_NICKNAME])
{
   char cmd[EOF_L_CMD+1];
   char id[EOF_L_ID+1];

   memset(cmd, 0, EOF_L_CMD+1);
   memset(id, 0, EOF_L_ID+1);

   eof_id_new(id);

   if(!eof_va_write(sockfd, 4, EOF_L_CMD, EOF_CMD_UI_PEER_RENAME,
                               EOF_L_ID, id,
                               EOF_L_NICKNAME, oldnick,
                               EOF_L_NICKNAME, newnick)) {
      return 0;
   }

   if(!eof_va_read(sockfd, 2, EOF_L_CMD, cmd, EOF_L_ID, id)) {
      return 0;
   }

   if(strncmp(cmd, EOF_CMD_UI_ACK, EOF_L_CMD)) {
      errno = 0; /* failure, but no library failure */
      read_all(sockfd, errmsg, EOF_L_MESSAGE);

      return 0; /* failure in any case */
   }

   return 1;
}
