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
 * Add a command to a category
 *
 */

#include <stdlib.h>     /* NULL           */
#include "ceofhack.h"   /* functions etc. */

int cmd_cat_add(unsigned long cat, struct cmd *cmd)
{
   struct cmd_cat *has_cat;

   has_cat = cmd_cat_find(cat);
   if(!has_cat> return 0;
/*   if(cmdlist_cnt >= HACK_CMD_CAT) return 0;

   cmdlist[cmdlist_cnt].cat = cat;
   cmdlist[cmdlist_cnt].first = NULL;

   ++cmdlist_cnt;

   */

   return 0;
}
