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
 * Show detailled peer information
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdlib.h>     /* calloc         */
#include <stdio.h>     /* printf         */
#include "ceofhack.h"  /* functions etc.  */

int peer_show(int fd[])
{
   struct peer *p;
   char nick[EOF_L_NICKNAME+1];
   char size[EOF_L_SIZE+1];
   char errmsg[EOF_L_MESSAGE+1];

   memset(nick, 0, EOF_L_NICKNAME+1);
   memset(size, 0, EOF_L_SIZE+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);

   if(!eof_va_read(fd[HP_READ], 1, EOF_L_NICKNAME, nick)) {
      perror("eof_va_read");
      return 0;
   }   

   printf("UI: peer show: %s\n", nick);
   p = peer_findbyname(nick);
   if(!p) {
      eof_errmsg("No such nick");
      if(!eof_va_write(fd[HP_WRITE], 2, EOF_L_CMD, EOF_CMD_UI_FAIL,
                                        EOF_L_MESSAGE, errmsg)) {
         perror("peershow/0");
      }
      return 0;
   }

   /* FIXME: currently only one address is supported */
   strncpy(size, "1", EOF_L_SIZE);
   if(!eof_va_write(fd[HP_WRITE], 4, EOF_L_CMD, EOF_CMD_UI_PEER_INFO,
                                    EOF_L_KEYID, p->keyid,
                                    EOF_L_SIZE, size,
                                    EOF_L_ADDRESS, p->addr)) {
      perror("peershow/1");
      return 0;
   }

   return 1;
}
