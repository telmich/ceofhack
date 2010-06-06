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
 * Registering UI
 *
 */

#include <stdio.h>      /* printf()          */
#include "ceofhack.h"   /* functions etc.    */

int cmd_2100(int fd[])
{
   char id[EOF_L_ID+1];

   id[EOF_L_ID] = 0;

   if(eof_va_read(fd[HP_READ], 1 , EOF_L_ID, id) != EOF_L_ID) return 0;

   printf("Successfully registered an UI (id=%s)\n", id);

   return (write_all(fd[HP_WRITE], EOF_CMD_UI_ACK, EOF_L_CMD) == EOF_L_CMD) ?
      1 : 0;
}
