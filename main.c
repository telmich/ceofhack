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
   int cnt;
   char buf[PATH_MAX+1];

   if(!config_init())   return 1;   /* read config          */
   if(!cgpg_init())     return 1;   /* init gpgme           */
   if(!signals_init())  return 1;   /* catch signals        */
   if(!cmds_init())     return 1;   /* enable commands      */
   if(!peers_init())    return 1;   /* empty peers          */

//   if(!tp_init())       return 1;   /* transport protocols  */
//   if(!ui_init())       return 1;   /* enable user input    */

   /* add stdin to poll */
   if(!helper_fdonly(STDIN_FILENO, user_input, NULL)) return 1;

   /* HACK: add tcp4 listener to poll */
   strncpy(buf, opt.home, PATH_MAX);
   strncat(buf, "/.ceof/transport-protocols/enabled/tcp4/get", PATH_MAX - strlen(opt.home));
   printf("using %s\n",buf);

   if(!helper_exec(buf, NULL, NULL)) return 1;

   while(1) {
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
