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
 * Disable all UIs
 *
 */

//#include <stdio.h>      /* printf         */
#include "ceofhack.h"   /* functions etc. */

void ui_disable_all()
{
   struct helper *hp;
   int i = 0;

   /* find UIs: every helper that has ui_read() registered */
   while((hp = helper_find_by_handle(&i, ui_read))) {
      ui_disable(hp->fds[HP_READ]);
   }
}
