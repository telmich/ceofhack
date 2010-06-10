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
 * Handle /peer rename request
 *
 */

#include <string.h>     /* memset()          */
#include <stdio.h>      /* printf()          */
#include "ceofhack.h"   /* functions etc.    */
#include "ceof.h"

int cmd_2104(int fd[])
{
   char oldnick[EOF_L_NICKNAME+1];
   char newnick[EOF_L_NICKNAME+1];
   char errmsg[EOF_L_MESSAGE+1];
   char id[EOF_L_ID+1];
   int ret;

   memset(oldnick, 0, EOF_L_NICKNAME+1);
   memset(newnick, 0, EOF_L_NICKNAME+1);
   memset(errmsg, 0, EOF_L_MESSAGE+1);
   memset(id, 0, EOF_L_ID+1);

   printf(CEOF_MSG_UIPROMPT "/peer rename request\n");
   
   if(!eof_va_read(fd[HP_READ], 3,
                   EOF_L_ID, id,
                   EOF_L_NICKNAME, oldnick,
                   EOF_L_NICKNAME, newnick)) {
      perror("eof_va_read");
      return 0;
   }
   printf(CEOF_MSG_UIPROMPT "/peer rename details: %s, %s\n", oldnick, newnick);

   ret = peer_rename(oldnick, newnick, errmsg);

   if(ret) {
      eof_va_write(fd[HP_WRITE], 4, EOF_L_CMD, EOF_CMD_UI_PEER_RENAMED,
                                    EOF_L_ID, id,
                                    EOF_L_NICKNAME, oldnick,
                                    EOF_L_NICKNAME, newnick);

   //   FIXME: also notify all users uis
   } else {
      eof_va_write(fd[HP_WRITE], 3, EOF_L_CMD, EOF_CMD_UI_FAIL, 
                                    EOF_L_ID, id,
                                    EOF_L_MESSAGE, errmsg);
   }   

   return ret;
}
