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
 * Add an available protocol
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */


#include "ceofhack.h"   /* functions etc. */

int tp_listen_add(char *name, struct cconfig entry)
{
   struct ltp ltpnew;
   struct cconfig *url;

   printf("Debug: %d in %s\n", entry.noe, entry.path);

   memset(ltpnew.url, '\0', sizeof(ltpnew.url));

   /* check for url */
   url = cconfig_find_fn("url", entry, NULL);

   /* something missing? */
   if(!url) {
      printf("LTP: Error: url missing for listening transport protocol %s!\n", name);
      return 0;
   }

   /* read url */
   if(!openreadclosestatic(ltpnew.url, url->path, EOF_L_ADDRESS)) return 0;

   if( (ltps_cnt+1) < EOF_L_LTP) {
      memcpy(&ltps[ltps_cnt], &ltpnew, sizeof(ltps[ltps_cnt]));

      ++ltps_cnt;
      printf("LTP %d %s listening at %s\n", ltps_cnt, name, ltpnew.url);
   } else {
      printf("LTP: Error: Maximum number of listening TPs!\n");
      return 0;
   }

   return 1;
}
