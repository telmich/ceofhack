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
 * Initialise an UI to work with ceof
 *
 */

#include <errno.h>      /* errno             */
#include "eof.h"        /* EOF*              */

int eof_ui_init(char id[EOF_L_ID])
{
   int tmp;

   errno = 0; /* reset in case we have the problem and not the library */
   if(!eof_id_init())                  { return -1; }
   if(!eof_id_new(id))                 { return -1; }

   if((tmp = eof_ui_connect()) == -1)  { return -1; }
   if(eof_ui_register(tmp, id) == -1)  { return -1; }

   return 1;
}
