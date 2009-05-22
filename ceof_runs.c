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
 * Check, if a file exists
 *
 */

#include <sys/types.h>     /* types          */
#include <sys/stat.h>      /* stat           */
#include <stdlib.h>        /* stat           */
#include <string.h>        /* memset()       */
#include <errno.h>         /* errno          */
#include <signal.h>        /* kill()         */
#include <unistd.h>        /* unlink()       */

#include <stdio.h>         /* debug          */

#include "shcl.h"          /* helper         */
#include "ceofhack.h"      /* internals      */

int ceof_runs()
{
   char pid_c[EOF_L_PIDLEN];
   pid_t pid;

   memset(pid_c, '\0', EOF_L_PIDLEN);

   if(fileexists(opt.pidfile)) {
      if(!openreadclosestatic(pid_c, opt.pidfile, EOF_L_PIDLEN)) {
         return -1;
      }
      pid = strtoul(pid_c, NULL, 10);

      if(kill(pid, 0) == 0)  {
         return pid;
      } else {
         printf("Removing stale pidfile %s (%d).\n", opt.pidfile, pid);
         if(unlink(opt.pidfile) == -1) {
            return -1;
         }
      }
   }

   /* BUUUUUUUUUUG */
   snprintf(pid_c, EOF_L_PIDLEN, "%d\n", opt.pid);
   printf("pid, pid_c: %d, %s", opt.pid, pid_c);

   if(!openwriteclose(opt.pidfile, pid_c, 7)) {
      return -1;
   }

   return 0;
}
