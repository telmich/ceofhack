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
#include "ceof.h"  /* functions etc.  */
#include "ceofhack.h"  /* functions etc.  */

struct peer *peer_findbyname(char *nick)
{
   struct peer *p;

   for(p = peers_list.next; p != NULL; p = p->next) {
      if(!strncmp(p->name, nick, EOF_L_NICKNAME)) {
         return p;
      }
   }

   return NULL;
}
