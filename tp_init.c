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
 * Init transport protocols
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */


#include "ceofhack.h"   /* functions etc. */

struct tp tps;

int tp_init()
{
   char buf[PATH_MAX+1];
   buf[PATH_MAX] = 0;
   struct cconfig cg;
//   struct cconfig *cgp, tmp, tmp2;

   /* build cconfig tree */
   if(!cconfig_tree(opt.tphome, &cg)) return 0;

   /* search for available protocols */
   strncpy(buf, opt.tphome, PATH_MAX);
   strncat(buf, "/available", PATH_MAX);
/*
   cgp = cconfig_find(buf);
   if(!cconfig_find(buf, &cgt)) return 0;
   if(!cgp) return 0;

   for(i = 0; i < cgp->noe; i++) {

   }

   while(cconfig_read(tmp, &tmp2)) {
      cconfig_

   }
*/
   /* search for enabled (listener) protocols */

   return 1;
}
