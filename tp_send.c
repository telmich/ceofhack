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
 * Send data to peer
 *
 */

#include <string.h>        /* strlen()          */
#include <unistd.h>        /* write()           */
#include <stdio.h>         /* NULL              */
#include "ceofhack.h"      /* functions etc.    */

int tp_send(char *nick, char *msg)
{
   char           *url;
   struct cconfig *send;
   struct helper  *hp;

   url = peer_addr_get(nick);
   printf("Using address %s for %s\n", url, nick);

   /* search for transport protocol */
   send = tp_available(url, TP_SEND);

   if(!send) {
      printf("No transport protocol available to send data to %s(%s)!\n", nick, url);
      return 0;
   }
   printf("Using %s to send to %s\n", send->path, url);

   /* create (onion) packet: post-0.1 release! */

   /* pass final packet to transport protocol:
    *
    * add packet to outgoing queue!
    *    --> verry important, because same happens in EOF-3!
    *    --> noise queue and real data are mixed
    * tp_insert_queue(pkg, peer / addr);
    * pipe into transport protocol
    * add pipe to poll list
    * return to work
    * on incoming message, read result of send
    * - resend if failed
    * - remove from queue, if successful!
    */

   if(!(hp = helper_exec(send->path, tp_send_wait, NULL))) return 0;

   /* HACK: pass packet to send */
   /* FIXME: add command, \n" */
   write(hp->fds[HP_WRITE], msg, strlen(msg));

   return 1;
}
