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
 * Stolen from cLinux/vsm: Handle incoming connection
 *
 *
 */

#include <unistd.h>     /* fork     */
#include <stdio.h>      /* perror   */
#include <stdlib.h>     /* *alloc   */

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "eof.h"   /* EOF */

int handle_conn(int sock)
{
   char input[EOF_L_PKG_MAX+1];
   ssize_t len;
   struct timespec ts;

   /* read init sequence: 1001 */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, "dummy-LTP cmd: %s\n", input);
   
   /* read the url */
   read(STDIN_FILENO, input, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, "dummy-LTP listens to url: %s\n", input);

   /* wait some time and drop a "received packet" */
   ts.tv_sec  = 3;
   ts.tv_nsec = 0;
   nanosleep(&ts, NULL);

//   len = write(STDOUT_FILENO, crypt, strlen(crypt));
//   fprintf(stderr, "len=%lu\n", strlen(crypt));


   /* read commands */
   while(1) {
      len = read(STDIN_FILENO, input, EOF_L_PKG_MAX+1);
      if(len < 0) {
         perror("tp/dummy/listen: read");
         return 1;
      }

      if(len > EOF_L_PKG_MAX) {
         fprintf(stderr, "Packet too big (%lu)!\n", len);
         continue;
      }
      input[len] = '\0';
      fprintf(stderr, "dummy-LTP received command: %s (until first \\0)\n", input);

      if(!strncmp(input, EOF_CMD_TPL_STOP, EOF_L_CMD)) {
         fprintf(stderr, "dummy/c: Time to say goodbye...\n");
         return 0;
      }
   }

   return 0;
}
}
