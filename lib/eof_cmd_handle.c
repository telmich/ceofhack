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
#include "ceofhack.h"      /* helper */

int eof_cmd_handle(unsigned long eofs, int fd[], ssize_t *rr)
{
   struct eof_cmd       *cmd;
   struct queue_entry   *qe;
   struct helper        *hp;

   char i_cmd[EOF_L_CMD];
   char i_id[EOF_L_ID];

   /* always read a command first */
   *rr = shcl_read_all(fd[EOF_CMD_READ], i_cmd, EOF_L_CMD);

   /* catch error and end-of-file */
   if(*rr < 1) return *rr;

   cmd = eof_cmd_find_in_cat(eofs, i_cmd);
   if(!cmd) cmd = eof_cmd_cat_get_default_cmd(eofs);

   /* entry in queue required ? */
   if(cmd->queue_req) {
      *rr = shcl_read_all(fd[EOF_CMD_READ], i_id, EOF_L_ID);
      if(*rr < 1) return *rr;

      qe = queue_pop_entry(eofs, i_id);

      if(qe) {
         /* check whether meta data matches queue entry */
         //queue_verify_source(qe, fd);
      } else {
         /* bogus packet - close connection */
         printf(CEOF_MSG_PROMPT "Bogus packet on %d\n", fd[EOF_CMD_READ]);
         hp = helper_find_by_fd(EOF_CMD_READ, fd);
         if(hp) helper_disable(hp);
         return 0;
      }
   }

   /* cmd knows that it has an entry */
   return cmd->handle(fd);
}
