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

#include <stdio.h>        /* NULL              */
#include "ceofhack.h"      /* functions etc.    */

int tp_send(char *nick, char *msg)
{
   char *url;

   url = peer_addr_get(nick);
   printf("Using address %s for %s\n", url, nick);

   /* get an address (URL) */

   //if(!helper_exec(tp->path, tp_listen_read, NULL)) return 0;

   //   if(!helper_exec(buf, peer_input, NULL)) return 1;


   return 1;
}
