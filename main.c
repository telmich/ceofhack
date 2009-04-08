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
#include "ceofhack.h"   /* functions etc. */

struct helper  chp[MAX_COMM];
struct pollfd  pfd[MAX_COMM];
int            chp_cnt = 0;
struct cconfig hometree;

int main()
{
   int cnt;

   if(!config_init())   return 1;   /* read config          */
   if(!cgpg_init())     return 1;   /* init gpgme           */
   if(!signals_init())  return 1;   /* catch signals        */
   if(!tp_init())       return 1;   /* transport protocols  */
   if(!ui_cmds_init())  return 1;   /* enable ui commands   */
   if(!peers_init())    return 1;   /* empty peers          */

   /* add stdin to poll: replace this later with a UI socket*/
   if(!helper_fdonly(STDIN_FILENO, user_input, NULL)) return 1;

// if(!ui_init())       return 1;   /* enable user input    */

   while(1) {
      /* reinit, poll array may have changed */
      fd_to_poll();

      cnt = poll(pfd, chp_cnt, -1);
      if(cnt == -1) {
         if(errno != EINTR) return 1;
      } else {
         check_input();
      }
   }

   return 0;
}
