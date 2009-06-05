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
#include <stdlib.h>     /* free()            */

#include "eof.h"        /* functions etc.    */

int main()
{
   char buf[PATH_MAX+1];
   char nick[EOF_L_NICKNAME+1];
   char newnick[EOF_L_NICKNAME+1];
   char keyid[EOF_L_KEYID+1];
   char addr[EOF_L_ADDRESS+1];
   char cmd[EOF_L_CMD+1];
   char msgtxt[EOF_L_MESSAGE+1];
   char errmsg[EOF_L_MESSAGE+1];
   char *p;

   int sockfd, i, nop;

   /* just for fun */
   eof_get_configdir(buf, PATH_MAX+1);
   printf("configdir: %s\n", buf);

   if((sockfd = eof_ui_init()) == -1) {
      perror("eof_ui_init");
      return 1;
   }

   if(eof_ui_register(sockfd) == -1) {
      perror("eof_ui_register");
      return 1;
   }

   /* terminate, so there is at least one \0 */
   buf[PATH_MAX] = 0;
   nick[EOF_L_NICKNAME] = 0;
   newnick[EOF_L_NICKNAME] = 0;
   keyid[EOF_L_KEYID] = 0;
   addr[EOF_L_ADDRESS] = 0;
   msgtxt[EOF_L_MESSAGE] = 0;
   errmsg[EOF_L_MESSAGE] = 0;

   /* eof_va_write is a low level function used by the library 
   if(!eof_va_write(sockfd, 4, EOF_L_CMD, cmd, EOF_L_NICKNAME, nick,
                    EOF_L_ADDRESS, addr, EOF_L_KEYID, keyid)) return 2;
    */

   /* peer add */
   strncpy(cmd, EOF_CMD_UI_PEER_ADD, EOF_L_CMD);
   strncpy(nick, "telmich", EOF_L_NICKNAME);
   strncpy(addr, "tcp:127.0.0.1:4242", EOF_L_ADDRESS);
   strncpy(keyid, "A310FB220BA776083559C8276A8817C51B70A5DF", EOF_L_KEYID);

   printf("Adding peer telmich \n");
   if(!eof_ui_peer_add(sockfd, errmsg, nick, addr, keyid)) {
      if(errno) {
         perror("eof_ui_peer_add");
      } else {
         printf("EOFi error: %s\n", errmsg);
      }
   }

   /* peer list */
   printf("First list of known peers\n");
   if((nop = eof_ui_peer_list(sockfd, errmsg, &p)) == -1) {
      if(errno) {
         perror("eof_ui_peer_list");
      } else {
         printf("/peer list EOFi error: %s\n", errmsg);
      }
   } else {
      printf("Peers:\n");
      for(i=0; i < nop; i++) {
         printf("   [%d]: %s\n", i, (p+ (i*(EOF_L_NICKNAME+1))));
      }
      free(p);
   }

   /* peer send */
   printf("Send message to telmich\n");
   strncpy(msgtxt, "Hallo, wie geht es?", EOF_L_MESSAGE);
   if(!eof_ui_peer_send(sockfd, errmsg, nick, msgtxt)) {
      if(errno) {
         perror("eof_ui_peer_send");
      } else {
         printf("/peer send EOFi error: %s\n", errmsg);
      }
   }

   /* peer rename */
   printf("Rename telmich -> telmich_new\n");
   strncpy(newnick, "telmich_new", EOF_L_NICKNAME);
   if(!eof_ui_peer_rename(sockfd, errmsg, nick, newnick)) {
      if(errno) {
         perror("eof_ui_peer_rename");
      } else {
         printf("/peer rename EOFi error: %s\n", errmsg);
      }
   }

   /* peer list, again */
   printf("Second /peer list\n");
   if((nop = eof_ui_peer_list(sockfd, errmsg, &p)) == -1) {
      if(errno) {
         perror("eof_ui_peer_list");
      } else {
         printf("/peer list EOFi error: %s\n", errmsg);
      }
   } else {
      printf("Peers:\n");
      for(i=0; i < nop; i++) {
         printf("   [%d]: %s\n", i, (p+ (i*(EOF_L_NICKNAME+1))));
      }
      free(p);
   }

   /* peer show */
   memset(keyid, 0, EOF_L_KEYID+1);
   p = NULL;
   printf("Show peer information for %s\n", newnick);
   if((nop = eof_ui_peer_show(sockfd, errmsg, newnick, keyid, &p)) == -1) {
      if(errno) {
         perror("eof_ui_peer_show");
      } else {
         printf("/peer show EOFi error: %s\n", errmsg);
      }
   } else {
      printf("Keyid: %s\n", keyid);
      printf("Addresses:\n");
      for(i=0; i < nop; i++) {
         printf("   [%d]: %s\n", i, (p+ (i*(EOF_L_ADDRESS+1))));
      }
      free(p);
   }

   /*
    * init stdin and EOFi listener like in EOFi, but vice versa
    */

   /* peer send */
   /* peer list */
   /* peer rename */
   /* peer show */
   /* quit */

   /* deregister */
   if(!eof_ui_deregister(sockfd)) {
      perror("eof_ui_derigester");
      return 255;
   }

   return 0;
}
