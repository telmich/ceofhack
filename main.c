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
 * The starting point
 *
 */

#include <poll.h>       /* guess what     */
#include <limits.h>     /* PATH_MAX       */
#include <stdio.h>      /* printf()       */
#include <string.h>     /* str()*         */
#include <errno.h>      /* guess what     */
#include <stdlib.h>     /* getenv         */
#include "ceofhack.h"  /* functions etc. */

int main()
{
   struct pollfd fds[HP_LAST];
   int cnt, i;
   struct helper ipv4l, user;
   char *home, buf[PATH_MAX+1];

   /* get homedir */
   home = getenv("HOME");
   if(!home) {
      fprintf(stderr, "you don't have a home, poor guy!\n");
      return 1;
   }

   /* create listener */
   strncpy(buf, home, PATH_MAX);
   strncat(buf, "/.ceof/transport-protocols/enabled/tcp4/get", PATH_MAX - strlen(home));
   printf("using %s\n",buf);

   if(!forkexecpipe(buf, &ipv4l)) return 1;

//   if(!init_gui()) return -1;



   while(0) {
      /* reinit fds, may habe changed 
      for(i=0; i < HP_LAST; i++) {
         fds[i].fd       =  opts->hp[i].fds[0];
         fds[i].events   =  POLLIN;
      } */

      cnt = poll(fds, HP_LAST, -1);
      if(cnt == -1 && errno != EINTR) return 0;
      
      /* check client interaction 
      for(i=0; i < HP_LAST; i++) {
         if(fds[i].revents & POLLIN) {
            opts->hp[i].handle(opts->hp[i].fds);
            --cnt;
         }
         if(!cnt) break;
      } */
   }

   return 1;
}
