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

   /* <empty> name <empty> addr */

   str++; /* skip whitespace */
   n = str;
   n = strchr(n, ' ');
   if(!n) { 
      printf("Usage: /peer add <name> <addr>\n");
      return 0;
   }

   strncpy(p->peer.name, str, EOF_L_NICKNAME);
   len = (n - str) <= EOF_L_NICKNAME ? (n - str) : EOF_L_NICKNAME;
   p->peer.name[len] = 0;

   n++; /* skip whitespace */
   strncpy(p->peer.addr, n, EOF_L_ADDRESS );

   p->next = plist.next;
   plist.next = p;

   printf("Peer %s added with address %s.\n",p->peer.name, p->peer.addr);

   return 1;
}
