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
 * Initialise configuration system
 *
 */

#include <string.h>     /* memset, str*   */
#include <stdio.h>      /* printf         */
#include <stdlib.h>     /* getenv         */
#include "ceofhack.h"   /* functions etc.  */

struct options opt;

int config_init()
{
   /* FIXME: should read env and so on later */

   char *p; 

   p = getenv("HOME");
   if(!p) {
      fprintf(stderr, "You don't have a home, poor $something!\n");
      return 1;
   }

   strncpy(opt.home, p, PATH_MAX);
   strncpy(opt.ceofhome, opt.home, PATH_MAX);
   strncat(opt.ceofhome, "/.ceof", PATH_MAX - strlen(opt.ceofhome));

   strncpy(opt.gpg, "/usr/bin/gpg", PATH_MAX);
   strncpy(opt.gpghome, opt.ceofhome, PATH_MAX);
   strncat(opt.gpghome, "/gpg", PATH_MAX - strlen(opt.gpghome));

   return 1;
}
