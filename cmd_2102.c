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
 * Handle /peer add request
 *
 */

#include <string.h>     /* memset()          */
#include <stdio.h>      /* printf()          */
#include "ceofhack.h"   /* functions etc.    */

int cmd_2102(int fd[])
{
   char nick[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
   char errmsg[EOF_L_MESSAGE+1];
   char keyid[EOF_L_KEYID+1];
   int ret;

   memset(nick, 0, EOF_L_NICKNAME+1);
   memset(addr, 0, EOF_L_ADDRESS+1);
   memset(keyid, 0, EOF_L_KEYID+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);

   printf("UI: /peer add request\n");
   
   if(!eof_va_read(fd[HP_READ], 3,
                   EOF_L_NICKNAME, nick,
                   EOF_L_ADDRESS, addr,
                   EOF_L_KEYID, keyid)) {
      perror("eof_va_read");
      return 0;
   }
   printf("UI: /peer add details: %s, %s, %s\n", nick, addr, keyid);

   if(peer_findbyname(nick)) {
      eof_va_write(fd[HP_WRITE], 1, EOF_L_CMD, EOF_CMD_UI_FAIL);
      strncpy(errmsg, "Peer already known", EOF_L_MESSAGE);
      eof_va_write(fd[HP_WRITE], 1, EOF_L_MESSAGE, errmsg);
      ret = 1;
   } else {
      ret = peer_add(nick, addr, keyid);

      if(ret) {
         eof_va_write(fd[HP_WRITE], 1, EOF_L_CMD, EOF_CMD_UI_ACK);
      } else {
         eof_va_write(fd[HP_WRITE], 1, EOF_L_CMD, EOF_CMD_UI_FAIL);
         strncpy(errmsg, "Hmm, /peer list failed!", EOF_L_MESSAGE);
         eof_va_write(fd[HP_WRITE], 1, EOF_L_MESSAGE, errmsg);
      }
   }

   return ret;
}
