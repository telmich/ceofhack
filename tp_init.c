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

struct tp tpa[EOF_L_TPA];
int    tpa_cnt;

struct tpl tpls[EOF_L_TPL];
int    tpls_cnt;

struct cconfig tp_tree;

int tp_init()
{
   char *p;
   struct cconfig tp_tree;
   struct cconfig tmp, entry;
   int state;

   /* init data list */
   memset(&tpa, '\0', sizeof(tpa));
   tpa_cnt = 0;

   /* build cconfig tree */
   strcpy(tp_tree.path, opt.tphome);
   if(!cconfig_tree(&tp_tree)) return 0;

   cconfig_tree_dump(tp_tree, 1);

   /* search for all available protocols */
   if(!cconfig_find_fn("available", tp_tree, &tmp)) {
      printf("No transport protocols available!\n");
      return 0;
   }

   state = 0;
   while(cconfig_entries_get(tmp, &entry, &state)) {
      p = cconfig_entry_fn(&entry);
      printf("Received %s (%s)\n", entry.path, p);

      if(!tp_add_available(p, entry)) return 0;
   }

   /* search for listening protocols */
   if(!cconfig_find_fn("listen", tp_tree, &tmp)) {
      printf("No listening transport protocols!\n");
      return 0;
   }

   state = 0;
   while(cconfig_entries_get(tmp, &entry, &state)) {
      p = cconfig_entry_fn(&entry);
      printf("Received listen %s (%s/%d)\n", entry.path, p, entry.noe);

      if(!tp_listen_add(p, entry)) return 0;
   }
 
   /* enable listener protocols */
   if(!tp_listen_init()) return 0;

   return 1;
}
