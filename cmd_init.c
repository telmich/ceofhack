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
 * Initialise commands in categories
 *
 */

#include "ceofhack.h"   /* functions etc. */

struct cmd_cat categories[EOF_CAT_MAX];

int cmd_init()
{
   struct cmd *newcmd;

   /* TRANSPORT PROTOCOL SENDING */
   if(!(newcmd = cmd_create(EOF_CMD_TPS_DEFAULT, cmd_20xx))) return 0;
   cmd_cat_init(EOF_CAT_TPS, newcmd);

   if(!(newcmd = cmd_create(EOF_CMD_TPS_SENT, cmd_2000))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_RECV, cmd_2002))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_LISTENING, cmd_2003))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   /* USER INTERFACE */
   if(!(newcmd = cmd_create(EOF_CMD_UI_DEFAULT, cmd_21xx))) return 0;
   cmd_cat_init(EOF_CAT_UI, newcmd);

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

   if(!(newcmd = cmd_create(EOF_CMD_UI_QUIT, cmd_2199))) return 0;
   if(!cmd_cat_add(EOF_I_UI, newcmd)) return 0;

//   if(!(newcmd = cmd_create(EOF_CMD_EXT_MESSAGE, cmd_3000))) return 0;
//   if(!cmd_cat_add(EXR, newcmd)) return 0;

   return 1;
}


/**** the idea

Get the queue/EOFs the fd is associated to.

   Table / Relation:

   EOFs        Initial commands (per EOFs)   Waiting commands

   LTP,        2100, ...                     2101
   TP,
   UI

If we get data on fd X, we search for a handler for this fd.
This handler already knows to which eofs it belongs.


NEXT:
   List of eofs

--------------------------------------------------------------------------------

General command handling:
x List of all EOFs
x For each EOFs type define possible commands
x For all commands define the type (question/answer)
x Define the handler for the command

The queue:
- Needs to belong to a EOFs type
- Needs to store the ID of questions
- Needs to store the command number of the question
- Need one queue per EOFs (even for the same type of EOFs)

****/

struct queue {
   struct eofs       *type;               /* pointer to type of EOFs       */
   int               fd;                  /* incoming data arrives here    */
   struct queueentry *next;               /* pointer to the first entry    */
};

struct queueentry {
   char              id[EOF_L_ID];
   struct cmd        cmd;                 /* the questioning command       */
   struct queueentry *next;               /* pointer to the next entry     */

};
