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
 * Create a command category
 *
 */

#include <stdio.h>      /* printf()       */
#include <stdlib.h>     /* NULL           */
#include "ceofhack.h"   /* functions etc. */

int cmd_cat_create(unsigned long cat, struct cmd *def)
{
   if(cmdlist_cnt >= HACK_CMD_CAT) {
      printf("Too many commands\n");
      return 0;
   }

   cmdlist[cmdlist_cnt].cat  = cat;
   cmdlist[cmdlist_cnt].next = NULL;
   cmdlist[cmdlist_cnt].def  = def;

   ++cmdlist_cnt;

   return 1;
}
