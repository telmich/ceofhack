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
 * Find a command in a category
 *
 */

#include <string.h>     /* strncmp()      */
#include "ceofhack.h"   /* functions etc. */

struct cmd *cmd_find_in_cat(unsigned long cat, char cmd[])
{
   struct cmd_cat *cc = cmd_cat_find(cat);
   struct cmd *c = NULL;

   if(!cc) return NULL;
   while((c = cc->next) != NULL) {
      if(!strncmp(cmd, c->num, EOF_L_CMD)) {
         break;
      }
   }

   return c;
}
