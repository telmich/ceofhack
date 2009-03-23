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
 * Init transport protocols
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */


#include "ceofhack.h"   /* functions etc. */

struct tp tps;

int tp_init()
{
   char *p;
   struct cconfig cg;
   struct cconfig tmp, entry;

   /* build cconfig tree */
   strcpy(cg.path, opt.tphome);
   if(!cconfig_tree(&cg)) return 0;

   cconfig_tree_dump(cg, 1);

   /* search for all available protocols */
   if(!cconfig_find_fn("available", cg, &tmp)) {
      printf("No transport protocols available!\n");
      return 0;
   }

   memset(&entry, '\0', sizeof(entry));
   while(cconfig_entries_get(tmp, &entry)) {
      p = cconfig_entry_fn(&entry);
      printf("Received %s (%s)\n", entry.path, p);
   }

   /* search for enabled (listener) protocols */

   return 1;
}
