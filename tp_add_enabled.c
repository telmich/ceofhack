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

int tp_add_enabled(char *name, struct cconfig entry)
{
   struct ltp ltpnew;
   struct cconfig *url;

   memset(ltpnew.url, '\0', sizeof(ltpnew.url));

   /* check for handler */
   ltpnew.listen  = cconfig_find_fn("listen", entry, NULL);
   url            = cconfig_find_fn("url", entry, NULL);

   /* something missing? */
   if(!ltpnew.listen || !url) {
      printf("TP: Error: dummy listening transport protocol %s!\n", name);
      return 0;
   }

   /* read url */
   if(!openreadclosestati(ltpnew.url, ltpnew.listen->path, EOF_L_ADDRESS)) return 0;

   if( (ltps_cnt+1) < EOF_L_LTP) {
      memcpy(&ltps[ltps_cnt], &ltpnew, sizeof(ltps[ltps_cnt]));

      ++tps_cnt;
   }
   printf("LTP %d %s successfully added\n", tps_cnt, name);

   return 1;
}
