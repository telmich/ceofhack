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

#include "ceofhack.h"  /* functions etc. */

int fd_to_poll(int fd, struct pollfd fds[], int *in_use)
{
   if((*in_use + 1) > MAX_COMM) return 0;

   fds[*in_use].fd = fd;
   fds[*in_use].events = POLLIN | POLLPRI;

   (*in_use)++;

   return 1;
}
