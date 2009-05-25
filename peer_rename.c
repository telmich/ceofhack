/*******************************************************************************
 *
 * 2009        Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Rename a peer
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdio.h>      /* printf         */

#include "ceofhack.h"   /* functions etc.  */
#include "eof.h"        /* EOF             */

int peer_rename(char oldnick[EOF_L_NICKNAME], char newnick[EOF_L_NICKNAME],
                char errmsg[EOF_L_MESSAGE])
{
   struct peer *p;

   p = peer_findbyname(oldnick);
   if(!p) {
      eof_errmsg("No such nick");
      return 0;
   }

   strncpy(p->name, newnick, EOF_L_NICKNAME);

   printf("/peer renamed: %s->%s\n",oldnick, p->name);

   return 1;
}
