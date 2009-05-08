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
   char plaintext[EOF_L_PKG_MAX+1];
   char *p, *endnum;
   ssize_t len, pkglen;

   printf("Received a packet!!!\n");

   len = read_all(fd[HP_READ], buf, EOF_L_PKG_MAX+1);
   if(len == -1) {
      perror("cmd2002/read");
      return 0;
   }
   printf("cmd2002 read %lu bytes in total\n", len);

   if(len > EOF_L_PKG_MAX) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet too big\n");
      return 0;
   }
   buf[len] = '\0'; /* terminate for print / debugging */

   p = strchr(buf, '\n');

   if(!p) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet is missing size information\n");
      return 0;
   }

   *p = '\0'; /* end of header reached */
   pkglen = strtol(buf, &endnum, 10);

   if(endnum != p) {
      printf("cmd2002: Broken packet: number of bytes is not directly followed by a newline\n");
      return 0;
   }

   p++; /* begin of real packet */

   if(pkglen != (len - (p - buf))) { /* position after \n -> end */
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: bogus size information in packet: %lu vs %lu!\n", pkglen,  (len - (p - buf)));
      return 0;
   }

   /* finally: print / decrypt the packet!
    * - decrypt
    * - forward to all UIs
    * - debug for now: print to stdout
    */

   printf("Incoming packet: %s\n", p);
   plaintext[0] = '\0';
   len = cgpg_decrypt(p, pkglen, plaintext, EOF_L_PKG_MAX);

   if(len > 0) {
      printf("Incoming plaintext [%lu]: %s\n", len, plaintext);
   } else {
      printf("decryption failed with %ld\n", len);
   }

   return 1;
//   return write_all(STDOUT_FILENO, p+1, pkglen) > 0 ? 1 :0;
}
