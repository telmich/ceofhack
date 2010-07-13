/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Add an item to the queue
 *
 */

#include <stdio.h>      /* NULL           */
#include <stdlib.h>     /* calloc         */
#include <string.h>     /* strncpy        */
#include <eof.h>
#include "ceofhack.h"   /* functions etc. */

struct queue_entry *queue_push_entry(int cat, char id[])
{
   struct queue_entry *qe;

   qe = calloc(1, sizeof(struct queue_entry));
   if(qe) {
      strncpy(qe->id, id, EOF_L_ID);

      /* add as first item */
      qe->next = queues[cat].first;
      queues[cat].first = qe;
   }

   return qe;
}
