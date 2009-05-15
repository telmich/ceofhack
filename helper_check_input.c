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
 * Which handler/fd received input? -> Delegate to handler
 *
 */

#include <unistd.h>     /* read           */
#include <stdio.h>      /* perror         */

#include "ceofhack.h"  /* functions etc. */

void helper_check_input(int possible, int *have_data)
{
   int i;
   struct helper *hp;

   for(i=0; i < possible && *have_data > 0; i++) {
      if(pfd[i].revents & (POLLIN | POLLPRI)) {
//         printf("data on channel %d\n",i);
         hp = helper_find_by_fd(HP_READ, pfd[i].fd);
         if(!hp) {
            /* there is i race condition when the child is cleared, but
               the poll list still contains the item. thus just ignore 
               this case.
            printf("BUG: Check input on %d/%d (fd=%d): no handler\n", i, possible, pfd[i].fd);
            */
         } else {
            printf("hci: %d, %d, %d, %d\n", i, pfd[i].fd, hp->fds[HP_READ], hp->fds[HP_WRITE]);
            /*
             * found fd in set of hp, submit the whole set, that is
             * save in the helper structure!
             */
            if(!hp->handle(hp->fds)) {
               printf("Handler for fd %d failed!\n", pfd[i].fd);
            }
            --(*have_data);
         }
      }
   }
}
