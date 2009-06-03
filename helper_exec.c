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
 * Helper that needs to be executed
 *
 */

#include <stdio.h>      /* DEBUG          */
#include <limits.h>     /* PATH_MAX       */
#include <stdlib.h>     /* NULL           */
#include <string.h>     /* str*           */
#include "ceofhack.h"   /* functions etc. */

struct helper *helper_exec(char *path, int (*handle)(int []), int (*exit)(int []))
{
   int num = helper_new();

   if(num == -1) return NULL;

   strncpy(chp[num].path, path, PATH_MAX);
   chp[num].handle   = handle;
   chp[num].exit     = exit;

   if(!forkexecpipe(&chp[num])) return NULL;

/*   printf("he (%d): %s: ", num, path);
   for(i=0; i<4; i++) {
      printf("%d: %d ", i, chp[num].fds[i]);
   }
   printf("\n"); */

   return &chp[num];
}
