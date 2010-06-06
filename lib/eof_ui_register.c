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
 * UI->EOFi: Register UI at EOFi
 *
 */

#include <stdio.h>      /* perror()          */
#include <string.h>     /* perror()          */

#include "shcl.h"   /* functions etc.    */
#include <eof.h>    /* defines           */

int eof_ui_register(int sockfd, char id[])
{
   if(!eof_id_new(id)) return -1;
   char answer[EOF_L_CMD];

   /* submit register command: cmd_2100.c */
   if(!eof_va_write(sockfd, 2, EOF_L_CMD, EOF_CMD_UI_REGISTER,
                               EOF_L_ID, id)) {
      return -1;
   }

   if(!eof_va_read(sockfd, 1, EOF_L_CMD, answer)) {
      return -1;
   }

   if(strncmp(answer, EOF_CMD_UI_ACK, EOF_L_CMD)) return 0;

    return 1;
}
