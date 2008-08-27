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
 * Find peer by name
 *
 */

#include <string.h>     /* memset, str*   */
#include "ceofhack.h"  /* functions etc.  */

struct peer *peer_findbyname(char *name)
{
   struct peers *p;

   for(p = plist.next; p != NULL; p = p->next) {
      if(!strncmp(p->peer.name, name, EOF_L_NICKNAME+1)) {
         return &(p->peer);
      }
   }

   return NULL;
}
