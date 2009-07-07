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

enum {                                    /* List of EOF subsystems        */
   EOF_EOFS_TPL,                          /* transport protocol listener   */
   EOF_EOFS_TPS,                          /* transport protocol sender     */
   EOF_EOFS_UI,                           /* user interfaces               */
   EOF_EOFS_MAX                           /* maximum number of EOFs types  */
};

enum {
   EOF_CMD_ASR = 1,
   EOF_CMD_QSN = 2
};

struct cmdnew {
   char              cmd[EOF_L_CMD];      /* ascii string                  */
   int               type;                /* question / answer             */
   int               (*handle)(int fd[]); /* handling function             */
   struct cmd        *answer[];           /* list of answers               */
   struct cmd        *next;               /* next in list                  */
};



int cmd_init()
{
   struct cmd *newcmd;
   cmdlist_cnt = 0; /* no categories available */

   struct cmdnew eofs_list[EOF_EOFS_MAX][] = {
      { /* EOF_EOFS_TPL */
         { EOF_CMD_TPS_SENT, EOF_CMD_ASR, cmd_2000, { cmd_20xx, cmd_21xx, NULL } },
      }
   };


   /* create categories */
   if(!(newcmd = cmd_create(EOF_CMD_TPS_DEFAULT, cmd_20xx))) return 0;
   if(!cmd_cat_create(EOF_I_TP, newcmd)) return 0;
   if(!(newcmd = cmd_create(EOF_CMD_UI_DEFAULT, cmd_21xx))) return 0;
   if(!cmd_cat_create(EOF_I_UI, newcmd)) return 0;

   /* TRANSPORT PROTOCOLS */
   if(!(newcmd = cmd_create(EOF_CMD_TPS_SENT, cmd_2000))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_RECV, cmd_2002))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   if(!(newcmd = cmd_create(EOF_CMD_TPL_LISTENING, cmd_2003))) return 0;
   if(!cmd_cat_add(EOF_I_TP, newcmd)) return 0;

   /* USER INTERFACE */
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

struct eofs eofs[EOF_EOFS_MAX];           /* all possible EOFs             */

struct cmd_answer {
   struct cmd        *cmd;
   struct cmd_answer *next;
};

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
