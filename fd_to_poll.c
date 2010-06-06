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
 * Add fd securely to poll list
 *
 */

#include <poll.h>
#include <stdio.h>

#include "ceofhack.h"  /* functions etc. */
#include "ceof.h"

void fd_to_poll(int *used)
{
   int i;

   *used = 0; /* no poll entries */

   /*
    * cycle through all possible connections (found in helper list)
    * if the handler is NULL, it's either disabled
    * or has never been initialised
    */
   for(i=0; i < MAX_COMM && *used <= chp_cnt; i++) {
      if(chp[i].handle) {
         printf(CEOF_MSG_PROMPT "Added poll item %d (fd: %d, helper %d: %s, %p)\n", *used,
                 chp[i].fds[HP_READ], i, chp[i].path, chp[i].handle);
         pfd[*used].fd = chp[i].fds[HP_READ];
         pfd[*used].events = POLLIN | POLLPRI;
         pfd[*used].revents = 0;
         (*used)++;
      }
   }
}
