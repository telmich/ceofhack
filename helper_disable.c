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
 * Disable helper
 *
 */

#include <unistd.h>     /* close()        */
#include <stdio.h>
#include "ceofhack.h"   /* functions etc. */

void helper_disable(struct helper *hp)
{
   hp->pid = 0;

   if(close_all(hp->fds[EOF_CMD_READ]) == -1) {
      perror("helper/close_r");
   }
   if(hp->fds[EOF_CMD_WRITE] != hp->fds[EOF_CMD_READ]) {
      if(close_all(hp->fds[EOF_CMD_WRITE]) == -1) {
         perror("helper/close_w");
      }
   }
   hp->fds[EOF_CMD_READ]  = -1;  /* does not match, if searchd by fd */
   hp->fds[EOF_CMD_WRITE] = -1;

   hp->path[0] = '\0';
   hp->handle  = NULL;
   hp->exit    = NULL;

   --chp_cnt; /* one less to search */
}
