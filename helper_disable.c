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
 * Disable helper
 *
 */

#include <unistd.h>     /* close()        */
#include "ceofhack.h"   /* functions etc. */

void helper_disable(struct helper *hp)
{
   hp->pid = 0;

   close(hp->fds[HP_READ]);
   close(hp->fds[HP_WRITE]);
   hp->fds[HP_READ]  = -1;  /* does not match, if searchd by fd */
   hp->fds[HP_WRITE] = -1;

   hp->path[0] = '\0';
   hp->handle  = NULL;
   hp->exit    = NULL;

   --chp_cnt; /* one less to search */
}
