/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * The sample user interface -- main
 *
 */

#include <stdio.h>      /* printf()          */
#include "eof.h"        /* functions etc.    */

int main()
{
   /* create socket,
      connect socket: ui_init.c */

   if(eof_ui_connect() == -1) {
      perror("eof_ui_connect");
      return 0;
   }
   /* submit register command: cmd_2100.c */
   /* peer add */
   /* peer send */
   /* peer list */
   /* peer rename */
   /* peer show */
   /* quit */

   return 1;
}
