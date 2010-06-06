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
 * UI->EOFi: De-Register UI at EOFi
 *
 */

#include <stdio.h>      /* perror()          */

#include "shcl.h"   /* functions etc.    */
#include <eof.h>    /* defines           */

int eof_ui_deregister(int sockfd)
{
   /* submit deregister command: cmd_2101.c */
   if(write_all(sockfd, EOF_CMD_UI_DEREGISTER, EOF_L_CMD) != EOF_L_CMD) {
      return 0;
   }

    return 1;
}
