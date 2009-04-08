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
 * Check for a valid user command or return
 *
 */

#include <stdio.h>      /* NULL */
#include <string.h>     /* str* */

#include "ceofhack.h"   /* functions etc. */

struct ui_cmd *ui_cmd_check(char *string) /* return handle + param */
{
   struct ui_cmd *cp = &ui_cmds;
   int tmp;

   /* skip the first (entry block) */
   for(cp = cp->next; cp != NULL; cp = cp->next) {
      tmp = strlen(cp->name);
      if(!strncmp(string, cp->name, tmp)) {
         return cp;
      }
   }

   return NULL;
}
