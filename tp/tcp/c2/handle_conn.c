/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-unix-vsm //@\\ schottelius.org)
 *
 *    part of cLinux/vsm
 *
 *    Copying: GPLv3 (If you need another license: contact me)
 *
 *    Handle connection
 */

#include <unistd.h>     /* fork     */
#include <stdio.h>      /* perror   */
#include <stdlib.h>     /* *alloc   */

#include "vsm-intern.h"

extern int forklock;

int handle_conn(int sock, struct options *opts, struct commands *cmds)
{
   /* we are the child: when to connect stdin / out? */
   /* setup environment */
   if(!env_init_smtp(sock)) return 1;

   /* execute on_connect 
   switch(stage_exec(STD "on_connect"))
      case -1:
      break;
      case  0:
      break;
      case  1:
      break;
   } */

   while(1) {
      /* read command */

      /* detect stage */
      //switch(smtp_cmd_exec(,)) {
      switch(1) {
         case -1: /* unknown command */
         break;
         case  0: /* error in stage */
         break;
         case  1: /* success */
         break;
      }
   }
}
