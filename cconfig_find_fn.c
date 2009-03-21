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
 * Find by filename
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*, memcpy                  */
#include <limits.h>              /* PATH_MAX                      */

#include "ceofhack.h"            /* cconfig structure             */

int cconfig_find_fn(char *fn, struct cconfig src, struct cconfig *dst)
{
   int i;
   char *p;

   for(i=0; i < src.noe; i++) {
      
      /* set to the last directory, if existent */
      p = strrchr(src.entries[i].path, '/');
      if(p) p++;
      else p = src.entries[i].path;

      printf("%d - %s - %s - %s\n", i, fn, src.entries[i].path, p);
      if(!strcmp(fn, p)) {      /* found it!               */
         printf("Found %s in %s\n", fn, src.path);
         if(dst != NULL) {                      /* only copy if dst given  */
            printf("And copying struct\n");
            memcpy(dst, &src.entries[i], sizeof(src.entries[i]));
         }

         return 1;
      }
   }

   return 0;
}
