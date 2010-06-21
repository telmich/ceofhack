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
   int fd_from_extern[EOF_L_RW_SIZE];
   int fd_to_extern[EOF_L_RW_SIZE];

   /* read from EOFi [0], write from extern [1] */
   if(pipe(&fd_from_extern[0]) == -1) {
      perror("pipe");
      return 0;
   }
   hp->fds[EOF_CMD_READ] = fd_from_extern[0];
   if(!close_on_exec(hp->fds[EOF_CMD_READ])) return 0;

   /* write from EOFi [1], read from extern [0] */
   if(pipe(&fd_to_extern[0]) == -1) {
      perror("pipe2");
      return 0;
   }
   hp->fds[EOF_CMD_WRITE] = fd_to_extern[1];
   if(!close_on_exec(hp->fds[EOF_CMD_WRITE])) return 0;


   hp->pid = fork();
   if(hp->pid == -1) {
      perror("fork");
      return 0;
   }

   /* parent */
   if(hp->pid > 0) { 
      /* remove unecessary fds */
      close(fd_to_extern[0]);
      close(fd_from_extern[1]);

      /* Don't block reads in ceof */
      if(fcntl(hp->fds[EOF_CMD_READ], F_SETFL, O_NONBLOCK) < 0) {
         perror("fcntl");
      }

      if(fcntl(hp->fds[EOF_CMD_WRITE], F_SETFL, O_NONBLOCK) < 0) {
         perror("fcntl");
      }

      return 1;
   }

   /* child: connect stdin and stdout */
   if(dup2(fd_to_extern[0], STDIN_FILENO) == -1) {
      perror("dup2: stdin");
      _exit(1);
   }

   if(dup2(fd_from_extern[1], STDOUT_FILENO) == -1) {
      perror("dup2: stdout");
      _exit(1);
   }

   argv[0] = hp->path;
   argv[1] = NULL;

   execv(hp->path, argv);
   perror("execv");
   _exit(1);
}
