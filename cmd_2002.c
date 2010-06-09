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
#include "ceof.h"       /* clean header      */
int cmd_2002(int fd[])
{
   char buf[EOF_L_PKG_MAX+1];
   char size[EOF_L_SIZE+1];
   char plaintext[EOF_L_PKG_MAX+1];
   char nick[EOF_L_NICKNAME];
   ssize_t len;

   memset(size, 0, EOF_L_SIZE+1);
   memset(buf, 0, EOF_L_PKG_MAX+1);
   memset(plaintext, 0, EOF_L_PKG_MAX+1);

   printf("Received a packet!!!\n");

   if(read_all(fd[HP_READ], size, EOF_L_SIZE) != EOF_L_SIZE) {
      perror("cmd2002/read");
      return 0;
   }
   len = strtol(size, NULL, 10);
   printf("cmd2002 pkg should be %ld bytes in total\n", (long) len);

   if(len > EOF_L_PKG_MAX) {
      /* FIXME: tell tp to drop the packet */
      printf("cmd2002: packet too big\n");
      return 0;
   }

   if(read_all(fd[HP_READ], buf, len) != len) {
      perror("cmd2002/read_pkg");
      return 0;
   }

   /* finally: print / decrypt the packet!
    * - decrypt
    * - forward to all UIs
    * - debug for now: print to stdout
    */

   printf("Incoming packet: %s\n", buf);
   len = cgpg_decrypt(buf, len, plaintext, EOF_L_PKG_MAX);

   if(len > 0) {
      printf("ceofhack> Incoming plaintext [%ld]: %s\n", (long) len, plaintext);
      strncpy(nick, "UNKNOWN", EOF_L_NICKNAME);
      if(!cmd_1103(nick, plaintext)) {
         printf(CEOF_MSG_UIPROMPT "Message did not reach all UIs\n");
      } else {
         printf(CEOF_MSG_UIPROMPT "Message reached all UIs\n");
      }
      return 1;
   } else {
      perror("decryption failed");
      return 0;
   }

//   return write_all(STDOUT_FILENO, p+1, pkglen) > 0 ? 1 :0;
}
