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

int tp_add_available(char *name, struct cconfig entry)
{
   int len;
   struct tp tpnew;

   /* check for handler */
   tpnew.listen = cconfig_find_fn("listen", entry, NULL);
   tpnew.send   = cconfig_find_fn("send", entry, NULL);

   /* none there? that's a boo boo! */
   if(!tpnew.listen && !tpnew.send) {
      printf("TP: Error: dummy transport protocol %s!\n", name);
      return 0;
   }

   len = strlen(name);
   if(len > EOF_L_ADDRESS) {
      printf("TP: Error: identifier (%s) to long (%d > %d)!\n", name, len, EOF_L_ADDRESS);
      return 0;
   }
   
   if( (tps_cnt+1) < EOF_L_TPA) {
      strncpy(tpnew.scheme, name, len);
      tpnew.scheme[len] = '\0';
      memcpy(&tps[tps_cnt], &tpnew, sizeof(tps[tps_cnt]));

      ++tps_cnt;
   }
   printf("TP %d %s successfully added\n", tps_cnt, name);

   return 1;
}
