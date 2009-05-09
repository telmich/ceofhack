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
 * Return next usable helper index or -1 on maximum number.
 *
 */

#include "ceofhack.h"  /* functions etc. */

int helper_signal_all(int sig)
{
   int i, ret = 1;

   for(i=0; i < MAX_COMM; i++) {
      if(chp[i].pid) {
         if(helper_signal(&chp[i], sig) == -1) {
            perror("helper_signal");
            ret = 0;
         }
      }
   }

   return ret;
}
