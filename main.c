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
#include <errno.h>      /* guess what     */
#include "ceofhack.h"  /* functions etc. */

int main()
{
   struct pollfd fds[HP_LAST];
   int cnt, i;

   if(!listen_ipv4()) return -1; /* FIXME: post 0.1: replace with general listen */

   if(!init_gui()) return -1;


   while(1) {
      /* reinit fds, may habe changed */
      for(i=0; i < HP_LAST; i++) {
         fds[i].fd       =  opts->hp[i].fds[0];
         fds[i].events   =  POLLIN;
      }

      cnt = poll(fds, HP_LAST, -1);
      if(cnt == -1 && errno != EINTR) return 0;
      
      /* check client interaction */
      for(i=0; i < HP_LAST; i++) {
         if(fds[i].revents & POLLIN) {
            opts->hp[i].handle(opts->hp[i].fds);
            --cnt;
         }
         if(!cnt) break;
      }
   }

   return 1;
}


}
