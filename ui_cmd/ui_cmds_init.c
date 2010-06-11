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
 * Init commands and handler
 *
 */

#include <stdlib.h>     /* NULL */
#include "ceofhack.h"   /* functions etc. */

struct ui_cmd ui_cmds;

int ui_cmds_init()
{
   ui_cmds.name   = NULL;
   ui_cmds.next   = NULL;
   ui_cmds.handle = NULL;

   if(!ui_cmd_add(EOF_UI_HELP, ui_help)) return 0; 
   
   if(!ui_cmd_add(EOF_UI_PEER_ADD,  peer_add))  return 0; 
   if(!ui_cmd_add(EOF_UI_PEER_LIST, peer_list)) return 0; 
   if(!ui_cmd_add(EOF_UI_PEER_SEND, peer_send)) return 0; 

   if(!ui_cmd_add(EOF_UI_QUIT, ui_quit)) return 0; 

   return 1;
}
