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
 * Get configuration directory; Buffer needs to be PATH_MAX+1
 * 
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdlib.h>     /* getenv         */
#include "ceofhack.h"   /* functions etc.  */

void eof_get_configdir(char buf[])
{
   char *p; 

   memset(buf, '\0', PATH_MAX+1);

   p = getenv("EOF_HOME");
   if(p) {
      strncpy(buf, p, PATH_MAX);
      return;
   }

   p = getenv("HOME");
   if(p) {
      strncpy(buf, p, PATH_MAX);
   }
   strncat(buf, EOF_P_CONFIGDIR, PATH_MAX);

}
