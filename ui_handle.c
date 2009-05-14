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
 * Create new socket and register it
 *
 */

#include <sys/socket.h> /* accept         */
#include <errno.h>      /* guess          */
#include <stdio.h>      /* printf()       */

#include "ceofhack.h"   /* functions etc. */

int ui_handle(int fds[])
{
   int nsock;

   while((nsock = accept(fds[HP_READ], NULL, NULL)) != -1) {
      /* accept socket and add to helper list */
      printf("UI: got connection\n");
      if(!helper_fdonly(nsock, &ui_read, NULL)) {
         return 0;
      }
   }

   /* FIXME: is EWOULDBLOCK posix? */
   if(errno & (EAGAIN | EWOULDBLOCK)) {
      nsock = 1;
   } else {
      perror("accept");
      nsock = 0;
   }

   return nsock;
}
