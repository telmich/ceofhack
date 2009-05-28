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
 * Pass incoming packet to all UIs
 *
 */

#include <stdio.h>      /* printf()          */
#include "ceofhack.h"   /* functions etc.    */
#include "eof.h"        /* functions etc.    */

int cmd_1103(char nick[EOF_L_NICKNAME], char msgtxt[EOF_L_MESSAGE])
{
   int i = 0;
   int ret = 1;
   struct helper *hp;

   printf("UI: message received: <%s> %s\n", nick, msgtxt);

   while((hp = helper_find_by_handle(&i, ui_read))) {
      if(!eof_va_write(hp->fds[HP_WRITE], 2, EOF_L_NICKNAME, nick,
                                             EOF_L_MESSAGE, msgtxt)) {
         perror("cmd_1103/eof_va_write");
         ret = 0;
      }
   }

   return ret;
}
