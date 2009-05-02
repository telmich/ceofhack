/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-unix-vsm //@\\ schottelius.org)
 *
 *    part of cLinux/vsm
 *
 *    Copying: GPLv3 (If you need another license: contact me)
 *
 *    Accept the connection
 */

#include <stdio.h>         /* NULL     */
#include <errno.h>         /* errno    */
#include <sys/socket.h>    /* accept   */

#include "vsm-intern.h"

extern struct options opts;
extern struct commands cmds[];

void sigio(int sock)
{
   int nsock;

   while((nsock = accept(sock, NULL, NULL)) != -1) {
      if(nsock == -1) {
         if(errno != EAGAIN) {
            perror("accept");
         }
         return;
      }
      handle_conn(nsock, &opts, cmds);
   }
}
