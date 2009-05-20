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
 * Add a peer
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdlib.h>     /* calloc         */
#include <stdio.h>     /* printf         */

#include "ceofhack.h"   /* functions etc.  */
#include "ui.h"         /* functions etc.  */

int peer_add(char nick[EOF_L_NICKNAME], addr[EOF_L_ADDRESS], keyid[EOF_L_KEYID])
{
   struct peer *p;

   p = peer_new();
   if(!p) return 0;

   /* nick */
   str = stncpy(p->nick, EOF_L_NICKNAME);
   str = ui_cmd_argncpy(str, p->peer.addr, EOF_L_ADDRESS);
   str = ui_cmd_argncpy(str, p->peer.keyid, EOF_L_KEYID);

   p->next = plist.next;
   plist.next = p;

   printf("/peer add: Added <%s>@<%s>:<%s>\n",p->peer.name, p->peer.addr, p->peer.keyid);

   return 1;
}
