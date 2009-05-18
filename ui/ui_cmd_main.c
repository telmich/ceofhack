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
 * The sample user interface -- main
 *
 */

#include <limits.h>     /* PATH_MAX          */
#include <stdio.h>      /* printf()          */
#include <string.h>     /* strncpy()         */
#include <errno.h>      /*                   */

#include "eof.h"        /* functions etc.    */

int main()
{
   char buf[PATH_MAX+1];
   char nick[EOF_L_NICKNAME+1];
   char keyid[EOF_L_KEYID+1];
   char addr[EOF_L_ADDRESS+1];
   char cmd[EOF_L_CMD+1];
   char errmsg[EOF_L_MESSAGE+1];

   int sockfd;

   /* create socket,
      connect socket: ui_init.c */

   eof_get_configdir(buf, PATH_MAX+1);
   printf("configdir: %s\n", buf);

   if((sockfd = eof_ui_connect()) == -1) {
      perror("eof_ui_connect");
      return 1;
   }
   /* submit register command: cmd_2100.c */

   if(!eof_cmd_2100(sockfd)) return 1;



   /*
    * init stdin and EOFi listener like in EOFi, but vice versa
    */

   /* peer add */
   strncpy(cmd, EOF_CMD_UI_PEER_ADD, EOF_L_CMD);
   strncpy(nick, "telmich", EOF_L_NICKNAME);
   strncpy(addr, "tcp:127.0.0.1:4242", EOF_L_ADDRESS);
   strncpy(keyid, "A310FB220BA776083559C8276A8817C51B70A5DF", EOF_L_KEYID);

   //if(!eof_va_write(sockfd, 4, EOF_L_CMD, cmd, EOF_L_NICKNAME, nick,
   //                 EOF_L_ADDRESS, addr, EOF_L_KEYID, keyid)) return 2;

   if(!eof_ui_peer_add(sockfd, errmsg, nick, addr, keyid)) {
      if(errno) {
         perror("eof_ui_peer_add");
      } else {
         printf("EOFi error: %s\n", errmsg);
      }
   }

   /* peer send */
   /* peer list */
   /* peer rename */
   /* peer show */
   /* quit */

   /* deregister */
   if(!eof_cmd_2101(sockfd)) return 255;

   return 0;
}
