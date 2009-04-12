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
 * TP received packet
 *
 */

#include <stdlib.h>     /* strtol()          */
#include <unistd.h>     /* read()            */
#include <string.h>     /* strchr()          */
#include "ceofhack.h"   /* functions etc.    */

int cmd_2002(int fd[])
{
   char buf[EOF_L_PKG_MAX+1];
   char *p;
   ssize_t len;
   int pkglen;

   printf("Received a packet!!!\n");

   len = read(fd[HP_READ], buf, EOF_L_PKG_MAX+1);
   if(len == -1) {
      perror("cmd2002/read");
      return 0;
   }
   if(len > EOF_L_PKG_MAX) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet too big\n");
      return 0;
   }

   p = strchr(buf, '\n');

   if(!p) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet is missing size information\n");
      return 0;
   }

   *p = '\0';
   pkglen = strtol(buf, NULL, 10);

   if(pkglen <= 0 || pkglen > EOF_L_PKG_MAX || pkglen > (len - (p-buf))) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: bogus size information in packet!\n");
      return 0;
   }

   /* finally: print / decrypt the packet!
    * - decrypt
    * - forward to all UIs
    * - debug for now: print to stdout
    */

   return write_all(STDOUT_FILENO, p+1, pkglen) > 0 ? 1 :0;
}
