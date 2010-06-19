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
#include <errno.h>      /* guess what        */
#include <stdlib.h>     /* getenv            */
#include <unistd.h>     /* STDIN_FILENO      */


#include <string.h>     /* memset            */

#include <eof.h>       /* EOF */
#include "crypto.h"    /* eof-crypto */


struct crypto_options opt;

int main(int argc, char **argv)
{
   char cmd[EOF_L_CMD+1];
   int fds[EOF_L_RW_SIZE];

   cmd[1] = 0;

   if(argc != 2) crypto_usage();

   strncpy(opt.cryptohome, argv[1], PATH_MAX);
   strncpy(opt.gpg, "/usr/bin/gpg", PATH_MAX);

   if(!crypto_gpg_init()) return 1;
   if(!crypto_cmd_init()) return 2;

   fds[EOF_CMD_READ] = STDIN_FILENO;
   fds[EOF_CMD_WRITE] = STDOUT_FILENO;
   
   while(1) {
      eof_cmd_handle(CEOF_CRYPTO_CAT_CEOF, fds);
   }

   return 0;
}
