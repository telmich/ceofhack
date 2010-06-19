/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Main module of ceof-crypto
 *
 */

#include <poll.h>       /* guess what        */
#include <limits.h>     /* PATH_MAX          */
#include <stdio.h>      /* printf()          */
#include <string.h>     /* str()*            */
#include <errno.h>      /* guess what        */
#include <stdlib.h>     /* getenv            */
#include <unistd.h>     /* STDIN_FILENO      */

#include "eof.h"       /* clean header      */


struct crypto_options opt;

int main(int argc, char **argv)
{

   if(argc != 2) crypto_usage();

   strncpy(opt.cryptohome, argv[1], PATH_MAX);
   strncpy(opt.gpg, "/usr/bin/gpg", PATH_MAX);
   

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
