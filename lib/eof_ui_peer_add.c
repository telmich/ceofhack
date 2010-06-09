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
 * UI->EOFi: Register a peer
 *
 */

#include <stdio.h>   /* perror()          */
#include <string.h>  /* strncmp()         */
#include <errno.h>   /*                   */

#include <eof.h>    /* defines           */
#include "shcl.h"   /* functions etc.    */

int eof_ui_peer_add(int sockfd, char errmsg[EOF_L_MESSAGE], char nick[EOF_L_NICKNAME],
                    char addr[EOF_L_ADDRESS], char keyid[EOF_L_KEYID])
{
   char cmd[EOF_L_CMD];
   char id[EOF_L_ID];

   eof_id_new(id);

   if(!eof_va_write(sockfd, 5, 
                    EOF_L_CMD, EOF_CMD_UI_PEER_ADD,
                    EOF_L_ID, id,
                    EOF_L_NICKNAME, nick,
                    EOF_L_ADDRESS, addr,
                    EOF_L_KEYID, keyid)) {
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
