/*******************************************************************************
 *
 * 2008      Nico Schottelius (nico-ceofhack at schottelius.org)
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

#include "ceofhack.h"   /* functions etc. */

int cmd_handle(unsigned long eofs, int fds[], char data[])
{
   struct cmd *cmd;

   printf("EOFs %lu: handling cmd %c%c%c%c\n", eofs,
            data[0], data[1], data[2], data[3]);

   cmd = cmd_find_in_cat(eofs, data);
   if(!cmd) {
      printf("No cmd function found for command, calling default cmd!\n");
      cmd = cmd_cat_default_cmd(eofs);
   } else {
      printf("CMD %s found...\n", cmd->num);
   }

   return cmd->handle(fds);
}
