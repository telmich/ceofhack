/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Check, if a file exists
 *
 */

#include <sys/stat.h>      /* stat           */
#include <errno.h>         /* errno          */

int fileexists(char *filename)
{
   struct stat buf;

   if(stat(filename, &buf) != 0) {
      if(errno == ENOENT) {
         return 0;
      } else {
         return -1;
      }
   }

   return 1;
}
