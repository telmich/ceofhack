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
 * Send message to a peer
 *
 */

#include <string.h>     /* memset, str*      */
#include <stdio.h>      /* printf            */
#include "ceofhack.h"   /* functions etc.    */

int peer_send(char nick[EOF_L_NICKNAME+1], char msg[EOF_L_MESSAGE+1],
              char errmsg[EOF_L_MESSAGE])
{
   struct peer *p;
   char buf[BIGBUF+1];
   int len;

   p = peer_findbyname(nick);
   if(!p) {
      eof_errmsg("Unknown peer");
      return 0;
   }

   printf("Encrypting message...\n");
   /* encrypt msg for $nick */
   if(!(len = cgpg_encrypt(nick, msg, buf, BIGBUF, errmsg))) return 0;
   printf("Encrypted message: %s\n", buf);
   
   printf("/peer send: Sending %s->%s ...\n", msg, nick);
   return tp_send(nick, buf, len, errmsg);
}
