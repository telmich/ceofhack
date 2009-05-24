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
 * UI->EOFi: List all peers
 * Returns number of peers, puts them into *res, concatenated, always
 * zero terminated strings
 */

#include <stdio.h>      /* perror()          */
#include <string.h>     /* strncmp()         */
#include <stdlib.h>     /* strtoul, calloc   */
#include <errno.h>      /*                   */

#include "shcl.h"       /* functions etc.     */
#include "eof.h"        /* defines            */

int eof_ui_peer_list(int sockfd, char errmsg[EOF_L_MESSAGE], char **res)
{
   char buf[EOF_L_CMD+EOF_L_SIZE+1];
   char *p;
   int i, nop; /* number of peers */

   memset(buf, 0, EOF_L_CMD+EOF_L_SIZE+1);

   if(!eof_va_write(sockfd, 1, EOF_L_CMD, EOF_CMD_UI_PEER_LIST)) {
      return -1;
   }

   if(read_all(sockfd, buf, EOF_L_CMD) != EOF_L_CMD) {
      return -1;
   }

   if(strncmp(buf, EOF_CMD_UI_PEER_LISTING, EOF_L_CMD)) {
      printf("returned cmd=%s (should be %s)\n", buf, EOF_CMD_UI_PEER_LISTING);
      errno = 0; /* failure, but no library failure */
      read_all(sockfd, errmsg, EOF_L_MESSAGE);

      return -1; /* failure in any case */
   }

   buf[EOF_L_SIZE] = 0;
   if(read_all(sockfd, buf, EOF_L_SIZE) != EOF_L_SIZE) {
      return -1;
   }

   nop = strtoul(buf, NULL, 10);
   *res = calloc(nop, EOF_L_NICKNAME+1);
   if(!(*res)) {
      strncpy(errmsg, "calloc()", EOF_L_MESSAGE);
      return -1;
   }

   for(i=0; i < nop; i++) {
      p = *res + (i * (EOF_L_NICKNAME+1));

      if(read_all(sockfd, p, EOF_L_NICKNAME) != EOF_L_NICKNAME) {
         return -1;
      }
   }

   return nop;
}
