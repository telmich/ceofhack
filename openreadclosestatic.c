/*******************************************************************************
 *
 * 2006-2009 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Read specific block from file
 * based openreadclose() from cinit
 * cinit: http://unix.schottelius.org/cinit/
 *
 *
 * Reads at most len bytes, but needs len+1 (for \0 at the end)
 *
 */

#include <unistd.h>             /* open, read, close */
#include <string.h>             /* strncpy */
#include <errno.h>              /* errno */
#include <stdio.h>              /* NULL */
#include <fcntl.h>              /* open */

int openreadclosestatic(char buf[], char *fn, int len)
{

   int tmp;
   int fd;

   while((fd = open(fn, O_RDONLY)) == -1) {
      if(errno != EINTR) {
         perror(fn);
         return 0;
      }
   }

   while(1) {
      tmp = read(fd, buf, len);

      if(tmp == -1) {
         if(errno == EINTR) {
            continue;
         } else {
            perror(fn);
            return 0;
         }
      }
      break;
   }
   buf[len] = '\0';

   while((fd = close(fd)) == -1) {
      if(errno == EINTR) {
         continue;
      } else {
         perror(fn);
         return 0;
      }
   }

   return 1;
}
