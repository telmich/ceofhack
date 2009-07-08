/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Read incoming data from a user interfaces
 *
 */

#include <unistd.h>     /* read           */
#include <stdio.h>      /* perror         */
#include "ceofhack.h"   /* functions etc. */

int ui_read(int fd[])
{
   char buf[EOF_L_CMD];
   int dbg;

   /* read command */
   if((dbg = read_all(fd[HP_READ], buf, EOF_L_CMD)) != EOF_L_CMD) {
      perror("ui_read");
      ui_disable(fd[HP_READ]);
      return 0;
   }
   printf("dbg: %d\n", dbg);

   printf("ui_read (cmd): %c%c%c%c\n", buf[0], buf[1], buf[2], buf[3]);

   return cmd_handle(EOF_CAT_UI, fd, buf);
}
