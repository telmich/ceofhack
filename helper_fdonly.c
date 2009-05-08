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
 * Helper that does not need to be executed, but has on open
 * fd already.
 *
 */

#include <signal.h>

#include "ceofhack.h"  /* functions etc. */

int helper_fdonly(int fd, int (*handle)(int []), int (*exit)(int []))
{
   int num = helper_new();

   if(num < 0) return 0;

   chp[num].pid            = 0;
   chp[num].fds[HP_READ]   = fd;
   chp[num].handle         = handle;
   chp[num].exit           = exit;

//   printf("Added fdonly: %d, %p\n", fd, handle);

   return 1;
}
