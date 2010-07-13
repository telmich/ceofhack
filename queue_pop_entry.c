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
 * Retrieve a queue entry and remove from queue
 *
 */

#include <stdio.h>      /* NULL           */
#include <string.h>     /* str*           */
#include <stdlib.h>     /* free           */
#include <eof.h>
#include "ceofhack.h"   /* functions etc. */

struct queue_entry *queue_pop_entry(int cat, char id[], struct queue_entry *save)
{
   struct queue_entry *qe, *qp;

   qp = qe = (queues[cat]).first;

   while(qe) {
      if(!strncmp(qe->id, id, EOF_L_ID)) {
         memcpy(save, qe, sizeof(struct queue_entry));

         /* remove qe from list and memory */
         qp->next = qe->next;
         free(qe);
         qe = save;

         break;
      }
      qp = qe;
      qe = qe->next;
   }

   return qe;
}
