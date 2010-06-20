/*******************************************************************************
 *
 * 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * List known peers
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdlib.h>     /* calloc         */
#include <stdio.h>     /* printf         */
#include "ceofhack.h"  /* functions etc.  */
#include "ceof.h"

int peer_list(int fd)
{
   struct peer *p;
   char intro[EOF_L_CMD+EOF_L_SIZE+1];
   int i = 0;

   for(p = peers_list.next; p != NULL; p = p->next) ++i;
   
   memset(intro, '\0', EOF_L_CMD+EOF_L_SIZE+1);
   strncpy(intro, EOF_CMD_UI_PEER_LISTING, EOF_L_CMD);
   snprintf(intro+EOF_L_CMD, EOF_L_SIZE, "%d", i);
   
   printf(CEOF_MSG_UIPROMPT "/peer list intro: %s\n", intro);
   if(shcl_write_all(fd, intro, EOF_L_CMD+EOF_L_SIZE) != (EOF_L_CMD+EOF_L_SIZE)) 
      return 0;

   for(p = peers_list.next; p != NULL; p = p->next) {
      printf(CEOF_MSG_UIPROMPT "/peer list: %s\n", p->name);
      if(shcl_write_all(fd, p->name, EOF_L_NICKNAME) != EOF_L_NICKNAME) {
         return 0;
      }
   }

   return 1;
}
