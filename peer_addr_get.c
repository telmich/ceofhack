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
 * Return address of peer
 *
 */

#include <string.h>     /* memset, str*   */
#include "ceofhack.h"  /* functions etc.  */

char *peer_addr_get(char *nick)
{
   struct peer *p;

   p = peer_findbyname(nick);
   if(!p) {
      printf("No such peer: %s!\n", nick);
      return NULL;
   }

   return p->addr;
}
