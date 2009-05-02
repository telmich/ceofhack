/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-unix-vsm //@\\ schottelius.org)
 *
 *    part of cLinux/vsm
 *
 *    Copying: GPLv3 (If you need another license: contact me)
 *
 *    does the socket handling
 */

#include <poll.h>          /* poll        */

#include "vsm-intern.h"    /* sigio       */

int do_socket(int sock)
{
   struct pollfd plist;

   plist.fd = sock;
   plist.events = POLLIN | POLLPRI;
   while(1) {
      if(poll(&plist, 1, -1) != -1) {
         if((plist.revents & POLLIN)  == POLLIN ||
            (plist.revents & POLLPRI) == POLLPRI) {
               sigio(sock);
         }
      }
   }
   return 0;
}
