/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Remove all ui stuff
 *
 */

#include <unistd.h>     /* unlink()       */
#include <stdio.h>      /* unlink()       */
#include "ceofhack.h"   /* functions etc. */
#include "ceof.h"

void ui_exit()
{
   printf(CEOF_MSG_UIPROMPT "Disabling all...\n");
   ui_disable_all();

   printf(CEOF_MSG_UIPROMPT "Removing socket...\n");
   if(unlink(opt.uisocket) == -1) {
      perror("ui_exit");
   }

}
