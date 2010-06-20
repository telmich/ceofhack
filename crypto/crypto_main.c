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

#include <sys/select.h> /* select()          */
#include <fcntl.h>      /* fcntl             */
#include <string.h>     /* memset            */

#include <eof.h>       /* EOF */
#include "crypto.h"    /* eof-crypto */


struct crypto_options opt;

int main(int argc, char **argv)
{
   char cmd[EOF_L_CMD+1];
   int fds[EOF_L_RW_SIZE];
   int tmp;
   ssize_t rr;
   fd_set readfds;

   cmd[1] = 0;

   if(argc != 2) crypto_usage();

   strncpy(opt.cryptohome, argv[1], PATH_MAX);
   strncpy(opt.gpg, "/usr/bin/gpg", PATH_MAX);

   if(!crypto_gpg_init()) return 1;
   if(!crypto_cmd_init()) return 2;

   fds[EOF_CMD_READ] = STDIN_FILENO;
   fds[EOF_CMD_WRITE] = STDOUT_FILENO;

   /* make sure that it's not blocking */
   tmp = fcntl(fds[EOF_CMD_READ], F_GETFL);
   tmp |= O_NONBLOCK;
   if(fcntl(fds[EOF_CMD_READ], F_SETFL, tmp) < 0) {
      perror("fcntl");
   }
   tmp = fcntl(fds[EOF_CMD_WRITE], F_GETFL);
   tmp |= O_NONBLOCK;
   if(fcntl(fds[EOF_CMD_WRITE], F_SETFL, tmp) < 0) {
      perror("fcntl");
   }
   
   while(1) {
      FD_ZERO(&readfds);
      FD_SET(fds[EOF_CMD_READ],&readfds);

      tmp = select(1, &readfds, NULL, NULL, NULL);
      if(tmp == -1) {
         if(errno != EINTR) {
            perror("select");
            return 1;
         }
      } else if (FD_ISSET(fds[EOF_CMD_READ],&readfds)) {
         if(( tmp = eof_cmd_handle(CEOF_CRYPTO_CAT_CEOF, fds, &rr)) < 1) {

            /* check for errors within read routine */
            if(rr == 0) {
               fprintf(stderr, "EOF reached!\n");
               return 1;
            } else if (rr == -1) {
               perror("cmd/read");
               return 1;
            }

            fprintf(stderr, "Handler failed, continuing ...\n");
         }
      }
   }

   return 0;
}
