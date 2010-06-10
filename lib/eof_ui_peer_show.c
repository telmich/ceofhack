/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * UI->EOFi: Show peer information
 * Returns number of addresses, puts them into *res, concatenated, always
 * zero terminated strings
 */

#include <stdio.h>      /* perror()          */
#include <string.h>     /* strncmp()         */
#include <stdlib.h>     /* strtoul, calloc   */
#include <errno.h>      /*                   */

#include "shcl.h"       /* functions etc.     */
#include "eof.h"        /* defines            */

int eof_ui_peer_show(int sockfd, char errmsg[EOF_L_MESSAGE],
                     char nick[EOF_L_NICKNAME], char keyid[EOF_L_KEYID],
                     char **addrs)
{
   char *p;
   int i, noa; /* number of addresses */

   char cmd[EOF_L_CMD+1];
   char size[EOF_L_SIZE+1];
   char id[EOF_L_ID+1];

   memset(cmd, 0, EOF_L_CMD+1);
   memset(size, 0, EOF_L_SIZE+1);
   memset(id, 0, EOF_L_ID+1);

   if(!eof_va_write(sockfd, 3, EOF_L_CMD, EOF_CMD_UI_PEER_SHOW,
                               EOF_L_ID, id,
                               EOF_L_NICKNAME, nick)) {
      return -1;
   }

   if(!eof_va_read(sockfd, 2, EOF_L_CMD, cmd,
                               EOF_L_ID, id)) {
      return -1;
   }

   if(strncmp(cmd, EOF_CMD_UI_PEER_INFO, EOF_L_CMD)) {
      printf("returned cmd=%s (should be %s)\n", cmd, EOF_CMD_UI_PEER_INFO);
      errno = 0; /* failure, but no library failure */
      read_all(sockfd, errmsg, EOF_L_MESSAGE);

      return -1; /* failure in any case */
   }

   if(!eof_va_read(sockfd, 2, EOF_L_KEYID, keyid,
                              EOF_L_SIZE, size)) {
      return -1;
   }

   noa = strtoul(size, NULL, 10);
   printf("Addresses reported from EOFi: %d\n", noa);

   *addrs = calloc(noa, EOF_L_ADDRESS+1);
   if(!(*addrs)) {
      strncpy(errmsg, "calloc()", EOF_L_MESSAGE);
      return -1;
   }

   for(i=0; i < noa; i++) {
      p = *addrs + (i * (EOF_L_ADDRESS+1));

      if(read_all(sockfd, p, EOF_L_ADDRESS) != EOF_L_ADDRESS) {
         return -1;
      }
   }

   printf("Addresses before end / from EOFi: %d\n", noa);
   return noa;
}
