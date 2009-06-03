/*******************************************************************************
 *
 * 2009     Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Wrapper for write() that continues on EINTR / incomplete write
 * Based on an idea of A. Pic. (eofdev at apic.name), 2009.
 *
 */

#include <unistd.h>     /* write          */
#include <errno.h>      /* EINTR          */
#include <stdio.h>      /* DEBUG          */

ssize_t write_all(int fd, const void *buf, size_t count)
{
   ssize_t tmp = 0;
   
   while(tmp != (ssize_t) count) {
      fprintf(stderr, "writing all %ld ...\n", (long) count);
      tmp = write(fd, buf, count);
      if(tmp == -1) {
         if(errno == EINTR) {
            continue;
         } else {
            return -1;
         }
      } else {
         break;
      }
   }
   
   return count;
}

