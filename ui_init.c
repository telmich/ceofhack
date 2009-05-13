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
 * Init user interface connection
 *
 */

//#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
//#include <string.h>              /* str*                          */
//#include <limits.h>              /* PATH_MAX                      */

#include <sys/socket.h> /* socket handling   */
#include <sys/un.h>     /* Unix socket       */

#include "ceofhack.h"   /* functions etc. */

int ui_init()
{
   int sock;
   struct sockaddr_un una;

   /* create socket */
   sock = socket(AF_UNIX, SOCK_STREAM, 0);
   if(sock == -1) {
      perror(opt.uisocket);
      return 0;
   }

   una.sun_family = AF_UNIX;
   /* FIXME: add length of una.sun_path */
   strcpy(una.sun_path, opt.uisocket);

   if(bind(sock, (struct sockaddr *) &una, sizeof(una)) == -1) {
      perror(opt.uisocket);
      return 0;
   }

   if(listen(sock, EOF_L_MAX_UI_WAIT) == -1) {
      perror(opt.uisocket);
      return 0;
   }

   /* add to helper list */

   return 1;
}
