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
 * Return helper with PID, if available
 *
 */

#include <sys/types.h>           /* POSIX for pid_t               */
#include <stdio.h>               /* NULL                          */
#include "ceofhack.h"            /* functions etc.                */

struct helper *helper_find_by_pid(pid_t pid)
{
   int i;

   for(i=0; i < MAX_COMM; i++) {
      if(chp[i].pid == pid) {
         return &chp[i];
      }
   }

   return NULL;
}
