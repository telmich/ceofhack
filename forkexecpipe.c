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
   printf("forkexecpipe: %s\n", path);

   /* read from EOFi, write from TP */
   if(pipe(&hp->fds[0]) == -1) {
      perror("pipe");
      return 0;
   }

   /* read from TP, write from EOFi */
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

   /* child */
   if(dup2(hp->fds[1], STDOUT_FILENO) == -1) {
      perror("dup2: stdout");
      _exit(1);
   }

   execv(path,NULL);
   perror("execv");
   _exit(1);
}
