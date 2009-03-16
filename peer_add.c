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
#include "ceofhack.h"  /* functions etc.  */

int peer_add(char *str)
{
   struct peers *p;
   char *n;
   int len;

   p = calloc(1, sizeof(struct peers));
   if(!p) return 0;

   /* <empty> name <empty> addr <empty> keyid */

   n = strchr(str, ' ');
   if(!n) { 
      printf("Usage: /peer add <name> <addr> <keyid>\n");
      return 0;
   }

   /* nick */
   strncpy(p->peer.name, str, EOF_L_NICKNAME);
   len = (n - str) <= EOF_L_NICKNAME ? (n - str) : EOF_L_NICKNAME;
   p->peer.name[len] = 0;

   str = n+1; /* skip whitespace */

   /* addr */
   strncpy(p->peer.addr, str, EOF_L_ADDRESS);
   n = strchr(str, ' '); /* seek to whitespace before keyid */
   len = (n - str) <= EOF_L_ADDRESS ? (n - str) : EOF_L_ADDRESS;
   p->peer.addr[len] = 0;

   str = n+1; /* skip whitespace */

   /* keyid: */
   /* FIXME: fail, if not equal id */
   strncpy(p->peer.keyid, str, EOF_L_KEYID);
   len = strlen(str) <= EOF_L_KEYID ? strlen(str) : EOF_L_KEYID;
   p->peer.keyid[len] = 0;

   p->next = plist.next;
   plist.next = p;

   printf("/peer add: Added <%s>@<%s>:<%s>\n",p->peer.name, p->peer.addr, p->peer.keyid);

   return 1;
}
