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
   int has_handler = TP_NOTHING, len;
   struct tp *tpnew;

   /* check for handler */
   if(cconfig_find_fn("listen", entry, NULL)) has_handler |= TP_LISTEN;

   /* none there? that's a boo boo! */
   if(has_handler == TP_NOTHING) {
      printf("TP: Error: dummy transport protocol %s!\n", name);
      return 0;
   }

   /* fillup list */
   tpnew = malloc(sizeof(struct tp));
   if(!tpnew) return 0;

   len = strlen(name);
   if(len > EOF_L_ADDRESS) {
      printf("TP: Error: identifier (%s) to long (%d > %d)!\n", name, len, EOF_L_ADDRESS);
      return 0;
   }
   
   /* fillup & add to list */
   strcpy(tpnew->scheme, name);
   tpnew->type = has_handler;
   tpnew->next = tps.next;
   tps.next = tpnew;
   
   printf("TP %s successfully added (%d)\n", name, tpnew->type);

   return 1;
}
