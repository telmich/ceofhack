/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-eof-1 //@\\ schottelius.org)
 *
 *    Was part of cLinux/vsm, now EOF-1
 *
 *    Copying: GPLv3 (If you need another license: contact me)
 *
 */

#include <sys/wait.h>      /* waitpid        */
#include <unistd.h>        /* exec*, pip     */
#include <stdio.h>         /* perror()       */

#include "ceofhack.h"          /* structures     */

int forkexecpipe(struct helper *hp)
{
   printf("forkexecpipe: %s\n", hp->path);

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

   /* parent */
   if(hp->pid > 0) { return 1; }

   /* child: connect stdin and stdout */
   if(dup2(hp->fds[2], STDIN_FILENO) == -1) {
      perror("dup2: stdin");
      _exit(1);
   }

   if(dup2(hp->fds[1], STDOUT_FILENO) == -1) {
      perror("dup2: stdout");
      _exit(1);
   }

   execv(hp->path, NULL);
   perror("execv");
   _exit(1);
}
