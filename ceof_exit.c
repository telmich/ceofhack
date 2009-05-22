/*******************************************************************************
 *
 * 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Leave ceofhack
 * - Shutdown helper: transport protocols, user interfaces
 * - [Send exit command to all and] send SIGINT
 *
 */

#include <signal.h>     /* kill()         */
#include <unistd.h>     /* _exit()        */
#include <time.h>       /* nanosleep()    */
#include "ceofhack.h"

void ceof_exit(int i)
{
   struct timespec ts;
   ts.tv_sec = 1;
   ts.tv_nsec =0;

   printf("Shutting down EOF subsystems (SIGINT)...\n");
   helper_signal_all(SIGINT);
   
   printf("Waiting %d seconds...\n", (short) ts.tv_sec);
   nanosleep(&ts, NULL);

   printf("Shutting down EOF subsystems (SIGKILL)...\n");
   helper_signal_all(SIGKILL);

   /* FIXME: replace with ui_disable_all() */
   printf("Removing UI socket...\n");
   unlink(opt.uisocket);

   _exit(i);
}
