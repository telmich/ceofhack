/*******************************************************************************
 *
 * 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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

#include <poll.h>       /* guess what        */
#include <limits.h>     /* PATH_MAX          */
#include <stdio.h>      /* printf()          */
#include <string.h>     /* str()*            */
#include <errno.h>      /* guess what        */
#include <stdlib.h>     /* getenv            */
#include <unistd.h>     /* STDIN_FILENO      */

#include "ceofhack.h"   /* functions etc.    */
#include "ceof.h"       /* clean header      */

struct pollfd  pfd[MAX_COMM];
struct cconfig hometree;

int main()
{
   int cnt;
   int pfd_cnt;

   ceof_banner(CEOF_MSG_VERSION);   /* up and starting..... */

   if(!config_init())   return CEOF_EX_CONFIG;     /* read config          */
   switch((cnt = ceof_runs())) {
      case -1:
         perror(CEOF_MSG_PROMPT "ceof_pidcheck");
         return CEOF_EX_RUNS_ERR;
      break;

      case 0: /* fine, we are alone */
      break;

      default: /* already running */
         printf(CEOF_MSG_PROMPT "An EOFi already runs (%d), exiting.\n", cnt);
         return CEOF_EX_RUNS;                         /* no need to restart   */
      break;
   }

   if(!eof_id_init())   return CEOF_EX_ID;         /* init id generator    */
   if(!helper_init())   return CEOF_EX_HELPER;     /* init helper structs  */
   if(!crypto_init())   return CEOF_EX_CRYPTO;     /* init crypto          */
   if(!signals_init())  return CEOF_EX_SIGNALS;    /* catch signals        */
   if(!cmd_init())      return CEOF_EX_CMD;        /* enable EOF commands  */
   if(!tp_init())       return CEOF_EX_TP;         /* transport protocols  */
   if(!peer_init())     return CEOF_EX_PEER;       /* handling of peers    */
   if(!ui_init())       return CEOF_EX_UI;         /* enable UI connector  */

   ceof_banner(CEOF_MSG_STARTED);   /* finally, we're there */
   while(1) {
      /* always reinit, poll array may have changed */
      fd_to_poll(&pfd_cnt);

      printf(CEOF_MSG_PROMPT "Polling %d helper channels...\n", pfd_cnt);
      cnt = poll(pfd, pfd_cnt, -1);
      if(cnt == -1) {
         if(errno != EINTR) {
            perror(CEOF_MSG_PROMPT "poll");
            return CEOF_EX_POLL;
         }
      } else {
         helper_check_input(pfd_cnt, &cnt);
      }
   }

   return 0;
}
