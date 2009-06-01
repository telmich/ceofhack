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
   char           *url, *p;
   struct cconfig *send;
   struct helper  *hp;
//   size_t         len;
   char           buf[BIGBUF+1];
   int            tmp;

   memset(buf, 0, BIGBUF+1);

   url = peer_addr_get(nick);
   printf("Using address %s for %s\n", url, nick);

   /* search for transport protocol */
   send = tp_available(url, TPS);

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
   snprintf(&buf[EOF_L_CMD+EOF_L_ADDRESS], EOF_L_SIZE+1, "%ld", (long) len);
   strncpy(&buf[EOF_L_CMD+EOF_L_ADDRESS], msg, len);
   len += EOF_L_CMD + EOF_L_ADDRESS;

   /* FIXME: HACK: pass packet to send        */
   if(helper_write(hp, buf, len) <= 0) {
      eof_errmsg("Data copy to transport protocol failed!");
      return 0;
   }

   return 1;

   /* old crap following */

   /* FIXME: always check bounds!!! */
   p = buf;
   strncpy(p, EOF_CMD_TPS, EOF_L_CMD);
   p += EOF_L_CMD;

   /* position after scheme */
   tmp = strlen(tp_getscheme(url)) + 1;
   strncpy(p, &url[tmp], EOF_L_ADDRESS);
   p += EOF_L_ADDRESS;

   len = strlen(msg);
   tmp = ultostr(len, 10, p, BIGBUF - (p-buf));

   len = EOF_L_CMD + EOF_L_ADDRESS + strlen(p) + 1 + strlen(msg);
   strncat(p, "\n", BIGBUF);
   strncat(p, msg, BIGBUF);

   /* FIXME: HACK: pass packet to send        */
   if(helper_write(hp, buf, len) <= 0) {
      eof_errmsg("Data copy to transport protocol failed!");
      return 0;
   }

   return 1;
}
