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
 * Add an available protocol
 *
 */

//#include <stdlib.h>              /* NULL                          */
//#include <stdio.h>               /* printf                        */
//#include <string.h>              /* str*                          */
//#include <limits.h>              /* PATH_MAX                      */

#include "ceofhack.h"   /* functions etc. */

int tp_start(struct tp *name, char *url, int type)
{
   struct cconfig *run;

   if(type & TPL) run = name->listen;
   else run = name->send;

   if(!run) {
      printf("Sorry %s protocol not available for %s!\n",
               type & TPL ? "listen" : "send",
               cconfig_...fn(name));
      return 0;
   }

   return 1;
}
