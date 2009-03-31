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
 * Check whether we have a handler for the url
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */


#include "ceofhack.h"   /* functions etc. */

struct cconfig *tp_available(char *url, int type)
{
   int i;

   for(i=0; i < tps_cnt; i++) {
      printf("LTP/TP: %s / %s [%lu]\n", url, tps[i].scheme, strlen(tps[i].scheme));
      if(!strncmp(url, tps[i].scheme, strlen(tps[i].scheme))) {
         if(type & TP_LISTEN && tps[i].listen) {
            return tps[i].listen;
         } else if(type & TP_SEND && tps[i].send) {
            return tps[i].send;
         }
      }
   }

   printf("NO TP found for URL %s!\n", url);

   return NULL;
}
