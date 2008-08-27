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
 * Handle user input
 *
 */

#include <unistd.h>     /* read */
#include <stdio.h>      /* perror         */
#include <string.h>     /* str*           */

#include "ceofhack.h"  /* functions etc. */

int user_input(int fd[])
{
   ssize_t len;
   struct cmd *cp;

   char buf[EOF_L_GUI+1];

   if((len = read(fd[0], buf, EOF_L_GUI)) == -1) {
      perror("read/ui");
      return 0;
   }
   /* strip \n, if present */
   if(buf[len-1] == '\n') {
      buf[len-1] = 0;
   } else {
      buf[len] = 0;
   }

   cp = cmd_check(buf);

   if(cp) {
      if(!cp->handle(buf + strlen(cp->name) + 1)) {
         printf("%s failed!\n", cp->name);
      }
   } else {
      printf("Sending text %s\n", buf);
//      msg_send(buf); /* no command? send as text */
   }

   return 1;
}
