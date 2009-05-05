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
      handle_conn(nsock);
   }
}
