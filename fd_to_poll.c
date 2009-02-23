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
 * Add fd securely to poll list
 *
 */

#include <poll.h>
#include <stdio.h>

#include "ceofhack.h"  /* functions etc. */

void fd_to_poll()
{
   int i;

   for(i=0; i < MAX_COMM; i++) {
      if(chp[i].handle) {
         printf("adding handler %d to poll list\n", i);
         pfd[i].fd = chp[i].fds[0];
         pfd[i].events = POLLIN | POLLPRI;
      } else {
         pfd[i].fd = -1;
         pfd[i].events = 0;
      }
      pfd[i].revents = 0;
   }
}
