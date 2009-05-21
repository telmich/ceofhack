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
#include "ceof.h"       /* clean header   */

struct pollfd  pfd[MAX_COMM];
struct cconfig hometree;

int main()
{
   int cnt;
   int pfd_cnt;

   ceof_banner(MSG_CEOF_VERSION);                   /* up and starting..... */

   if(!config_init())   return 1;   /* read config          */
   if(!helper_init())   return 1;   /* init helper structs  */
   if(!cgpg_init())     return 1;   /* init gpgme           */
   if(!signals_init())  return 1;   /* catch signals        */
   if(!cmd_init())      return 1;   /* enable EOF commands  */
   if(!tp_init())       return 1;   /* transport protocols  */
   if(!peer_init())     return 1;   /* handling of peers    */
   if(!ui_init())       return 1;   /* enable UI connector  */

   ceof_banner(MSG_CEOF_STARTED);                   /* finally, we're there */
   while(1) {
      /* always reinit, poll array may have changed */
      fd_to_poll(&pfd_cnt);

   //   printf("Polling on %d channels...\n", pfd_cnt);
      cnt = poll(pfd, pfd_cnt, -1);
      if(cnt == -1) {
         if(errno != EINTR) {
            perror("poll");
            return 1;
         }
      } else {
         helper_check_input(pfd_cnt, &cnt);
      }
   }

   return 0;
}
