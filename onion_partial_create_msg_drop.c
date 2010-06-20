/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Create a partial onion containing a message and drop command
 *
 */

#include <fcntl.h>               /* fcntl()                       */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <unistd.h>      /* unlink           */

#include <sys/socket.h> /* socket handling   */

#include "ceofhack.h"   /* functions etc.    */
#include "shcl.h"       /* helper            */
#include "ceof.h"

#include <eof.h>

void onion_partial_create_msg_drop(char id[], char msg[], char pkg[])
{
   /* FIXME: noise needed */
   char addr[EOF_L_ADDRESS];
   char group[EOF_L_GROUP];
   

   onion_partial_create(EOF_CMD_ONION_MSG_DROP, id, addr, group, msg, pkg);

}
