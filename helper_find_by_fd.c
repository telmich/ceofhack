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
 * Find *fd* on pipe-part *num*
 *
 */

#include <stdio.h>               /* NULL */
#include "ceofhack.h"            /* functions etc.                */

struct helper *helper_find_by_fd(int num, int fd)
{
   int i;

//   printf("Searching for %d at %d\n", fd, num);

   /* FIXME: chp_cnt == total number, not highest index number
    * looping through more helper than necessary in worst case, because
    * after we found chp_cnt, we can stop search...
    */
   for(i=0; i < MAX_COMM; i++) {
      if(chp[i].fds[num] == fd) {
//         printf("Found helper at %d\n", i);
         return &chp[i];
      }
   }

/* is valid, when child exited and poll list still contains fd */
//   printf("No helper found for fd=%d (helper possibly exited)\n", fd);
   return NULL;
}
