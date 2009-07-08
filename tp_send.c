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
 * Send data to peer
 *
 */

#include <string.h>        /* strlen()          */
#include <stdio.h>         /* NULL              */
#include "ceofhack.h"      /* functions etc.    */

int tp_send(char *nick, char *msg, int len, char errmsg[EOF_L_MESSAGE])
{
   char           *url;
   struct cconfig *send;
   struct helper  *hp;
   char           buf[BIGBUF+1];

   memset(buf, 0, BIGBUF+1);

   url = peer_addr_get(nick);
   printf("Using address %s for %s\n", url, nick);

   /* search for transport protocol */
   send = tp_available(url, EOF_CAT_TPS);

   if(!send) {
      eof_errmsg("No transport protocol available!");
      return 0;
   }
   printf("TP: Using %s to send to %s\n", send->path, url);

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

   if(!(hp = helper_exec(send->path, tp_send_wait, NULL))) {
      eof_errmsg("Transport protocol failed!");
      return 0;
   }

   strncpy(buf, EOF_CMD_TPS, EOF_L_CMD);
   strncpy(&buf[EOF_L_CMD], url, EOF_L_ADDRESS);

   /* snprintf uses only len bytes including \0, but we want it excluding */
   snprintf(&buf[EOF_L_CMD+EOF_L_ADDRESS], EOF_L_SIZE+1, "%ld", (long) len);

   printf("TP: pkg=%s, size=%s\n", buf, &buf[EOF_L_CMD+EOF_L_ADDRESS]);

   strncpy(&buf[EOF_L_CMD+EOF_L_ADDRESS+EOF_L_SIZE], msg, len);
   len += EOF_L_CMD + EOF_L_ADDRESS + EOF_L_SIZE;

   /* FIXME: HACK: pass packet to send        */
   if(helper_write(hp, buf, len) <= 0) {
      eof_errmsg("Data copy to transport protocol failed!");
      return 0;
   }

   return 1;
}
