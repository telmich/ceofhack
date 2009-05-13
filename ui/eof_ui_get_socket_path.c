/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Return the socket path
 *
 */

#include <limits.h>     /* PATH_MAX          */
#include <stdio.h>      /* printf()          */
#include <sys/socket.h> /* socket handling   */
#include <sys/un.h>     /* Unix socket       */

#include "eof.h"        /* EOF*              */

int eof_ui_connect()
{
   char sockpath[PATH_MAX];
   int sock;
   struct sockaddr_un una;

   sock = socket(AF_UNIX, SOCK_STREAM, 0);
   if(sock == -1) { return -1; }

   eof_get_ui_socket_path(una.sun_path);

   if(connect(sock, (struct sockaddr *) &una, sizeof(una)) == -1) {
      return -1;
   }

   return sock;
}
