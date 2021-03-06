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
 * Fork and exec a programm, connect its stdin and stdout back
 * to us. 
 * 
 * Was part of cLinux/vsm, now EOF-1
 * 
 */

#include <unistd.h>        /* exec*, pip     */
#include <stdio.h>         /* perror()       */
#include <fcntl.h>         /* fcntl          */

#include "ceofhack.h"          /* structures     */

int forkexecpipe(struct helper *hp)
{
   char *argv[2];

   /* read from EOFi [0], write from TP [1] */
   if(pipe(&hp->fds[0]) == -1) {
      perror("pipe");
      return 0;
   }

   /* write from EOFi [3], read from TP [2] */
   if(pipe(&hp->fds[2]) == -1) {
      perror("pipe2");
      return 0;
   }

   hp->pid = fork();
   if(hp->pid == -1) {
      perror("fork");
      return 0;
   }

   /* mark parent fds to be closed on exec (for _any_ child, not only this one) */
   if(!close_on_exec(hp->fds[HP_READ])) return 0;
   if(!close_on_exec(hp->fds[HP_WRITE])) return 0;

   /* parent */
   if(hp->pid > 0) { 
      /* Don't block reads in ceof */
      if(fcntl(hp->fds[HP_READ], F_SETFL, O_NONBLOCK) < 0) {
         perror("fcntl");
      }

      /* remove unecessary fds */
      close(hp->fds[HP_EXT_READ]);
      close(hp->fds[HP_EXT_WRITE]);

      return 1;
   }

   /* child: connect stdin and stdout */
   if(dup2(hp->fds[2], STDIN_FILENO) == -1) {
      perror("dup2: stdin");
      _exit(1);
   }

   if(dup2(hp->fds[1], STDOUT_FILENO) == -1) {
      perror("dup2: stdout");
      _exit(1);
   }

   argv[0] = hp->path;
   argv[1] = NULL;

   execv(hp->path, argv);
   perror("execv");
   _exit(1);
}
