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
   char size[EOF_L_SIZE+1];
   char plaintext[EOF_L_PKG_MAX+1];
   char nick[EOF_L_NICKNAME];
   char *p;
   ssize_t len, pkglen;

   memset(size, 0, EOF_L_SIZE+1);

   printf("Received a packet!!!\n");

   len = read_all(fd[HP_READ], buf, EOF_L_PKG_MAX+1);
   if(len == -1) {
      perror("cmd2002/read");
      return 0;
   }
   printf("cmd2002 read %ld bytes in total\n", (long) len);

   if(len > EOF_L_PKG_MAX) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet too big\n");
      return 0;
   }
   buf[len] = '\0'; /* terminate for print / debugging */

   strncpy(size, buf, EOF_L_SIZE);
   pkglen = strtol(size, NULL, 10);

   if(pkglen != (len - EOF_L_SIZE)) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: bogus size information in packet: %ld vs %ld!\n", 
         (long) pkglen,  (long) (len - (p - buf)));
      return 0;
   }

    if(pkglen <= 0) {
      printf("cmd2002: Packet too small (%ld Bytes)\n", (long) pkglen);
      return 0;
   }

   /* finally: print / decrypt the packet!
    * - decrypt
    * - forward to all UIs
    * - debug for now: print to stdout
    */

   p = &buf[EOF_L_SIZE];
   printf("Incoming packet: %s\n", p);
   plaintext[0] = '\0';
   len = cgpg_decrypt(p, pkglen, plaintext, EOF_L_PKG_MAX);

   if(len > 0) {
      printf("ceofhack> Incoming plaintext [%ld]: %s\n", (long) len, plaintext);
      strncpy(nick, "UNKNOWN", EOF_L_NICKNAME);
      if(!cmd_1103(nick, plaintext)) {
         printf("UI: Message did not reach all UIs\n");
      } else {
         printf("UI: Message reached all UIs\n");
      }
   } else {
      printf("decryption failed with %ld\n", (long) len);
   }

   return 1;
//   return write_all(STDOUT_FILENO, p+1, pkglen) > 0 ? 1 :0;
}
