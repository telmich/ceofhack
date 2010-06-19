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
 * Create a new command
 *
 */

#include <stdio.h>      /* printf            */
#include <stdlib.h>     /* malloc, NULL      */
#include <eof.h>        /* functions etc.    */

struct eof_cmd *eof_cmd_create(char num[], int (*handle)(int []))
{
   struct eof_cmd *new;

   new = malloc(sizeof(struct eof_cmd));
   if(!new) return NULL;

   new->num    = num;
   new->handle = handle;

   return new;
}
