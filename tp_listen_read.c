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
 * Read incoming data from a listening transport protocol
 *
 */

#include <unistd.h>     /* read           */
#include <stdio.h>      /* perror         */
#include "ceofhack.h"   /* functions etc. */

int tp_listen_read(int fd[])
{
   ssize_t len;
   char buf[BIGBUF+1];

   /* FIXME: always read  4 bytes (cmd) */
   if((len = read(fd[0], buf, EOF_L_CMD)) == -1) {
      perror("read/tp_listen");
      return 0;
   }
   buf[EOF_L_CMD] = '\0';
   printf("cmd received & ignored: %s\n", buf);
   return 1;


   /* read data into buffer until eof */
   if((len = read(fd[0], buf, BIGBUF)) == -1) {
      perror("read/tp_listen");
      return 0;
   }
   /* strip \n, if present */
   if(buf[len-1] == '\n') {
      buf[len-1] = 0;
   } else {
      buf[len] = 0;
   }

   /* send ACK to transport protocol */

   printf("data received: %s\n", buf);

   /* decrypt data, read command, choose function to use */

   return 1;
}
