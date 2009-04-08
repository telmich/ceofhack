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
 * Init commands and handler
 *
 */

#include <stdlib.h>

#include "ceofhack.h"  /* functions etc. */

int ui_cmd_add(char *name, int (*handle)(char *))
{
   struct ui_cmd *new;

   new = malloc(sizeof(struct ui_cmd));
   if(!new) return 0;

   new->name   = name;
   new->handle = handle;
   new->next   = ui_cmds.next;

   ui_cmds.next   = new;

   return 1;
}
