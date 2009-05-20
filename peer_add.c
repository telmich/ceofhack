/*******************************************************************************
 *
 * 2008-2009 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Add a peer
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdio.h>      /* printf         */

#include "ceofhack.h"   /* functions etc.  */
#include "eof.h"        /* EOF             */

int peer_add(char nick[EOF_L_NICKNAME], char addr[EOF_L_ADDRESS],
             char keyid[EOF_L_KEYID])
{
   struct peer *p;

   p = peer_new();
   if(!p) return 0;

   /* nick */
   strncpy(p->name, nick, EOF_L_NICKNAME);
   strncpy(p->addr, addr, EOF_L_ADDRESS);
   strncpy(p->keyid, keyid, EOF_L_KEYID);

   p->next = plist.next;
   plist.next = p;

   printf("/peer add: Added <%s>@<%s>:<%s>\n",p->name, p->addr, p->keyid);

   return 1;
}
