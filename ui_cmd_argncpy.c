/*******************************************************************************
 *
 * 2008-2009 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Copy this argument (similar to strncpy, copies at most max+1 characters)
 *
 */

#include <string.h>     /* str* */

#include "ceofhack.h"   /* functions etc. */

char *ui_cmd_argncpy(char *arglist, char dst[], size_t max)
{
   char *p;
   size_t len;

   p = strchr(arglist, ' ');
   if(!p) {
      p = arglist;
      len = 0;
      while(*p++) {
         ++len;
      }
   } else {
      len = (p - arglist);
      len = len > max ? max : len;
   }

   if(len) {
      strncpy(dst, arglist, len);
      return ++p;
   } else {
      return NULL;
   }
}
