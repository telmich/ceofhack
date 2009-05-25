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
 * Handle /peer send request
 *
 */

#include <string.h>     /* memset()          */
#include <stdio.h>      /* printf()          */
#include "ceofhack.h"   /* functions etc.    */

int cmd_2103(int fd[])
{
   char nick[EOF_L_NICKNAME+1];
   char msgtxt[EOF_L_MESSAGE+1];
   char errmsg[EOF_L_MESSAGE+1];
   char keyid[EOF_L_KEYID+1];
   int ret;

   memset(nick, 0, EOF_L_NICKNAME+1);
   memset(msgtxt, 0, EOF_L_MESSAGE+1);
   memset(keyid, 0, EOF_L_KEYID+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);

   printf("UI: /peer send request\n");
   
   if(!eof_va_read(fd[HP_READ], 2,
                   EOF_L_NICKNAME, nick,
                   EOF_L_MESSAGE, msgtxt)) {
      perror("eof_va_read");
      return 0;
   }
   printf("UI: /peer send details: %s, %s\n", nick, msgtxt);

   ret = peer_send(nick, msgtxt, errmsg);

   if(ret) {
      eof_va_write(fd[HP_WRITE], 1, EOF_L_CMD, EOF_CMD_UI_ACK);
   } else {
      eof_va_write(fd[HP_WRITE], 1, EOF_L_CMD, EOF_CMD_UI_FAIL);
      eof_va_write(fd[HP_WRITE], 1, EOF_L_MESSAGE, errmsg);
   }   

   return ret;
}
