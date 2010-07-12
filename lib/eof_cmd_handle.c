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
#include "shcl.h"      /* helper */

int eof_cmd_handle(unsigned long eofs, int fd[], ssize_t *rr)
{
   struct eof_cmd *cmd;
   char i_cmd[EOF_L_CMD];
   char i_id[EOF_L_ID];

   /* always read a command first */
   *rr = shcl_read_all(fd[EOF_CMD_READ], i_cmd, EOF_L_CMD);

   /* catch error and end-of-file */
   if(*rr < 1) {
      return *rr;
   }

   cmd = eof_cmd_find_in_cat(eofs, i_cmd);
   if(!cmd) {
      cmd = eof_cmd_cat_get_default_cmd(eofs);
   }

   /* entry in queue required ? */
   if(cmd->queue_req) {

      queue_entry_find(eofs, 

   }

   return cmd->handle(fd);
}
