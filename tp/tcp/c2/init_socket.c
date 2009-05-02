/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-unix-vsm //@\\ schottelius.org)
 *
 *    part of cLinux/vsm
 *
 *    Copying: GPLv3 (If you need another license: contact me)
 *
 *    Implements socket initialisiation
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>     /* write       */
#include <arpa/inet.h>  /* htons       */
#include <string.h>     /* memset      */
#include <stdlib.h>
#include <sys/poll.h>   /* poll        */
#include <stdio.h>      /* perror()    */

//#include "vsm-intern.h"
//#include "vsm-generic.h"
//#include "rfc2821.h"

#define PORT         1024+25
#define MY_IP        "0.0.0.0"   /* where we listen to */
#define SOCK_QUEUE   32          /* maximum elements in queue */

int init_socket(int *gsock)
{
   int tmp, sock;
   char ip[32] = MY_IP;
   struct sockaddr_in ins;

   memset(&ins, 0, sizeof(ins));
   ins.sin_family = AF_INET;
   ins.sin_port   = htons(PORT);
   if(!inet_aton(ip, &(ins.sin_addr) ) ) {
      write(2,"broken ipn\n",11);
      return 0;
   }

   sock = socket(PF_INET, SOCK_STREAM, 0);
   if(sock == -1 ) {
      perror("socket");
      return 0;
   }

   tmp = 1;
   // lose the pesky "Address already in use" error message
   if(setsockopt(sock,SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp)) == -1) {
      perror("setsockopt");
      return 0;
    }

   if(bind(sock,(struct sockaddr *)&ins,sizeof(ins)) == -1) {
      perror("bind");
      return 0;
   }

   /* start listening */
   if(listen(sock, SOCK_QUEUE) == -1) {
      perror("listen");
      return 0;
   }

   *gsock = sock;

   return 1;
}
