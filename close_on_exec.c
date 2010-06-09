/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Mark fd to be closed on exec
 *
 * Code adapted from http://www.opengroup.org/onlinepubs/009695399/functions/fcntl.html
 *
 */

#include <stdio.h>      /* perror         */
#include <fcntl.h>      /* fcntl...       */

int close_on_exec(int fd)
{
   int flags = fcntl(fd, F_GETFD);

   if(flags == -1) {
      perror("fcntl/F_GETFD");
      return -1;
   }
   flags |= FD_CLOEXEC;

   if(fcntl(fd, F_SETFD, flags) == -1) {
      perror("fcntl/F_SETFD");
      return -1;
   }

   return 1;
}

