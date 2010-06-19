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
 * Handle SIGCHILD
 *
 */

#include <sys/wait.h>   /* waitpid()         */
#include <stdio.h>      /* printf            */
#include "ceofhack.h"   /* functions etc.    */

void signal_child(int tmp)
{
   /* 
    * go through known children list
    * and restart where necessary or remove from helper
    * list!
    */
   pid_t pid;
   struct helper *hp;

   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      printf("Child %d died...\n", pid);

      hp = helper_find_by_pid(pid);
      if(!hp) {
         printf("Something useless exited\n");
         continue;
      }

      printf("Child %s exited (removing from poll list)!\n", hp->path);
      
      helper_disable(hp);
   }
}
