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
#include <unistd.h>     /* STDIN_FILENO   */
#include "ceofhack.h"  /* functions etc. */

struct helper chp[MAX_COMM];
struct pollfd pfd[MAX_COMM];
int chp_cnt = 0;

int main()
{
   int cnt, i;
   struct helper ipv4l, user;
   char *home, buf[PATH_MAX+1];

   if(!signals_init()) return 1;
   if(!cmds_init()) return 1;

   /* get homedir */
   home = getenv("HOME");
   if(!home) {
      fprintf(stderr, "You don't have a home, poor guy!\n");
      return 1;
   }

   /* add stdin to poll */
   if(!helper_fdonly(STDIN_FILENO, user_input, NULL)) return 1;

   /* add tcp4 listener to poll */
   strncpy(buf, home, PATH_MAX);
   strncat(buf, "/.ceof/transport-protocols/enabled/tcp4/get", PATH_MAX - strlen(home));
   printf("using %s\n",buf);
   if(!helper_exec(buf, NULL, NULL)) return 1;


//   if(!init_gui()) return -1;

   while(1) {
      printf("polling\n");
      /* reinit, poll array may have changed */
      fd_to_poll();

      cnt = poll(pfd, HP_LAST, -1);
      if(cnt == -1) {
         if(errno != EINTR) return 1;
      } else {
         check_input();
      }
   }

   return 0;
}
