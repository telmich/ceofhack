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

int forkexecpipe(char *path, struct helper *hp)
{
   if(pipe(hp->fds) == -1) {
      perror("pipe");
      return 0;
   }

   hp->pid = fork();
   if(hp->pid == -1) {
      perror("fork");
      return 0;
   }

   /* parent */
   if(hp->pid > 0) { return 1; }

   /* child */
   if(dup2(hp->fds[1], STDOUT_FILENO) == -1) {
      perror("dup2: stdout");
      _exit(1);
   }

   execv(path,NULL);
   perror("execv");
   _exit(1);
}
