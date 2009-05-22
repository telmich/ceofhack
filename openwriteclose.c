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
 * Open a file, write it, close it.
 *
 */

#include <unistd.h>             /* open, read, close */
#include <string.h>             /* strncpy */
#include <errno.h>              /* errno */
#include <stdio.h>              /* NULL */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>              /* open */


int openwriteclose(char *fn, char buf[], int len)
{
   int tmp;
   int fd;
   int got=0;

   while((fd = open(fn, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
      if(errno != EINTR) {
         perror(fn);
         return 0;
      }
   }

   while(got < len) {
      tmp = write(fd, buf+got, len-got);

      if(tmp == -1) {
         if(errno == EINTR) {
            continue;
         } else {
            perror(fn);
            return 0;
         }
      }
      if(!tmp) break;
      got += tmp;
   }

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
