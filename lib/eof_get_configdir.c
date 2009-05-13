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

#include "eof.h"   /* functions etc.  */

void eof_get_configdir(char buf[], size_t len)
{
   char *p; 

   memset(buf, '\0', len);

   p = getenv(EOF_ENV_EOF_HOME);
   if(p) {
      strncpy(buf, p, len);
      return;
   }

   p = getenv(EOF_ENV_HOME);
   if(p) {
      strncpy(buf, p, len);
   }
   strncat(buf, EOF_P_SLASH, len-1);
   strncat(buf, EOF_P_CONFIGDIR, len-1);

}
