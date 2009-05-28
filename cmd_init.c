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
 * Initialise command handler tree (similar to ui_cmd_init)
 *
 */

#include "ceofhack.h"   /* functions etc. */

/* global array */
struct cmd_cat cmdlist[HACK_CMD_CAT];
int cmdlist_cnt;

int cmd_init()
{
   struct cmd *newcmd;
   cmdlist_cnt = 0; /* no categories available */

   /* create categories */
   if(!(newcmd = cmd_create(EOF_CMD_TPS_DEFAULT, cmd_20xx))) return 0;
   if(!cmd_cat_create(EOF_I_TP, newcmd)) return 0;
   if(!(newcmd = cmd_create(EOF_CMD_UI_DEFAULT, cmd_21xx))) return 0;
   if(!cmd_cat_create(EOF_I_UI, newcmd)) return 0;

   /* create commands and add them to a category  */
   if(!(newcmd = cmd_create(EOF_CMD_TPS_SENT, cmd_2000))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_RECV, cmd_2002))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_LISTENING, cmd_2003))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_REGISTER, cmd_2100))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_DEREGISTER, cmd_2101))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_PEER_ADD, cmd_2102))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_PEER_SEND, cmd_2103))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_PEER_RENAME, cmd_2104))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_PEER_SHOW, cmd_2105))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_UI_PEER_LIST, cmd_2106))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

//   if(!(newcmd = cmd_create(EOF_CMD_EXT_MESSAGE, cmd_3000))) return 0;
//   if(!cmd_cat_add(EXR, newcmd)) return 0;

   return 1;
}
