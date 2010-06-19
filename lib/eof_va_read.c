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
 * Read a variable number of arguments, which are passed in pairs:
 * In case of nof = 2:
 * 
 *    eof_va_read(1, 2, len1, buf1, len2, buf2);
 *
 */

#include <stdarg.h>  /* va_*)             */

#include "shcl.h"    /* functions etc.    */
#include <eof.h>     /* defines           */

int eof_va_read(int fd, int nof, ...) /* nof = number of fields */
{
   va_list ap;
   int len;
   char *data;

   va_start(ap, nof);
   
   while(nof > 0) {
      len =    va_arg(ap, int);
      data =   va_arg(ap, char *);

      if(shcl_read_all(fd, data, len) != len) {
         return 0;
      }

      --nof;
   }

   va_end(ap);

   return 1;
}
