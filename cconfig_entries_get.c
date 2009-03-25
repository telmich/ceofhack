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
 * Return all entries, next needs to be zero initialised
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*, memcpy                  */
#include <limits.h>              /* PATH_MAX                      */

#include "ceofhack.h"            /* cconfig structure             */

int cconfig_entries_get(struct cconfig tree, struct cconfig *next, int *state)
{
   if(*state < tree.noe) {
      printf("Copying entry %d of %d, %s\n", *state, tree.noe, tree.path);
      
      memcpy(next, &tree.entries[*state], sizeof(tree.entries[*state]));
      (*state)++;
      
      return 1;
   }
      
   return 0;
}
