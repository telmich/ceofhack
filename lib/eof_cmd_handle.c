/*******************************************************************************
 *
 * 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Read incoming data from a listening transport protocol
 *
 */

#include <unistd.h>     /* read           */
#include <stdio.h>      /* perror         */

#include <eof.h>       /* functions etc. */

int eof_cmd_handle(unsigned long eofs, int fd[])
{
   struct cmd *cmd;
   char data[EOF_L_CMD];
   int len;

   /* always read a command first */
   if((len = read(fd[HP_READ], data, EOF_L_CMD)) == -1) {
      perror("cmd_handle/cmd");
      return 0;
   }

   printf(CEOF_MSG_PROMPT "EOFs %lu: handling cmd %c%c%c%c\n", eofs,
            data[0], data[1], data[2], data[3]);

   cmd = cmd_find_in_cat(eofs, data);
   if(!cmd) {
      printf(CEOF_MSG_PROMPT "No cmd function found for command, calling default cmd!\n");
      cmd = cmd_cat_get_default_cmd(eofs);
   } else {
      printf(CEOF_MSG_PROMPT "CMD %s found...\n", cmd->num);
   }

   return cmd->handle(fd);
}
