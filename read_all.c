/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Read all incoming data, up to count
 *
 */

#include <unistd.h>     /* write          */
#include <errno.h>      /* errno          */

ssize_t read_all(int fd, void *buf, size_t count)
{
   while(read(fd, buf, count) == -1) {
      if(errno == EINTR) { /* retry */
         continue;
      } else {
         return -1;
      }
   }
   
   return count;
}
