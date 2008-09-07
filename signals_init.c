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
 * Add references to functions
 *
 */

#include <signal.h>     /* sigaction   */
#include <stdio.h>      /* NULL  */

#include "ceofhack.h"  /* functions etc. */

int signals_init()
{
   struct sigaction sa;

   sa.sa_handler = signal_child;
   sa.sa_flags   = SA_NOCLDSTOP;

   if(sigaction(SIGCHLD, &sa, NULL) == -1) {
      perror("sigaction");
      return 0;
   }

   return 1;
}
