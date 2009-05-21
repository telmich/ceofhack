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

#include <fcntl.h>               /* fcntl()                       */
#include <stdio.h>               /* printf                        */
//#include <string.h>              /* str*                          */
#include <unistd.h>      /* unlink           */

#include <sys/socket.h> /* socket handling   */
#include <sys/un.h>     /* Unix socket       */

#include "ceofhack.h"   /* functions etc.    */
#include "shcl.h"       /* helper            */

int ui_init()
{
   int sock;
   struct sockaddr_un una;

   /* check for old socket */
   if(fileexists(opt.uisocket) == 1) {
      if(unlink(opt.uisocket) == -1) {
         perror(opt.uisocket);
         return 0;
      }
   }

   /* create socket */
   sock = socket(AF_UNIX, SOCK_STREAM, 0);
   if(sock == -1) {
      perror(opt.uisocket);
      return 0;
   }

   una.sun_family = AF_UNIX;
   /*
    * POSIX BUG: no length of sun_path defined:
    * http://www.opengroup.org/onlinepubs/9699919799/basedefs/sys_un.h.html
    */
   strcpy(una.sun_path, opt.uisocket);

   if(bind(sock, (struct sockaddr *) &una, sizeof(una)) == -1) {
      perror(opt.uisocket);
      return 0;
   }

   if(listen(sock, EOF_L_MAX_UI_WAIT) == -1) {
      perror(opt.uisocket);
      return 0;
   }

   /* set to non-blocking */
   fcntl(sock, F_SETFL, O_NONBLOCK, 1);

   /* add to helper list */
   if(!helper_fdonly(sock, sock, ui_handle, NULL)) return 0;

   return 1;
}
