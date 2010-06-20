/*******************************************************************************
 *
 * 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
   char pkg[EOF_L_PKG_MAX+1];
   char pkg_id[EOF_L_ID+1];

   p = peer_findbyname(nick);
   if(!p) {
      eof_errmsg("Unknown peer");
      return 0;
   }
   printf("/peer send: Sending %s->%s ...\n", msg, nick);

   /* create partial onion packet */
   onion_partial_create_msg_drop(pkg_id, msg, pkg);


   /* register into queue for retrieval of pkg */
   eof_id_new(pkg_id);

//   queue_add(queue_id, pkg_id, fptr);

   /* send encrypt msg for $keyid */
//   crypto_encrypt_request(pkg_id, pkg);
   
   /* handle send in queue handler */
//   return tp_send(nick, buf, len, errmsg);
   return 1;
}
