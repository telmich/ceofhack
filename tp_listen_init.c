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
 * Check and init listening protocols
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */


#include "ceofhack.h"   /* functions etc. */

int tp_listen_init()
{
   int i;
//   struct cconfig *listen;
 
   for(i=0; i < ltps_cnt; i++) {
      /* has handler? */
      
      if(!(ltps[i].listen = tp_listen_available(ltps[i]))) return 0;

      /* start it:
       * cwd to dir
       * argv1 = url
      */
//      if(!tp_listen_start(listen))) return 0;

   }

   return 1;
}
