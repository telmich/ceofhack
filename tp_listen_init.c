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
 * Check and init listening protocols
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <stdio.h>               /* printf                        */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */


#include "ceofhack.h"   /* functions etc. */

int tp_listen_init()
{
   int i, len;
   struct helper *hp;
   char cmd[EOF_L_CMD+EOF_L_ADDRESS+1]; /* FIXME: +1 is only for testing */

   strncpy(cmd, EOF_TPCMD_INIT_LTP, EOF_L_CMD);
   cmd[EOF_L_CMD+EOF_L_ADDRESS] = '\0';
 
   for(i=0; i < ltps_cnt; i++) {
      /* has handler? */
      if(!(ltps[i].listen = tp_available(ltps[i].url, TP_LISTEN))) return 0;

      /* start it:
       * - FIXME: cwd to dir before!
       * - add handler for LTP (generic?): tp_listen_read
       * - send 1001<url> cmd
       * 
       */

      /* FIXME: cwd into configdir */

      if(!(hp = helper_exec(ltps[i].listen->path, tp_listen_read, NULL))) return 0;

      /* FIXME: cwd back */

      /* FIXME: write start command including URL (excluding scheme) */
      len = tp_scheme_len(ltps[i].url);
      strncpy(cmd+EOF_L_CMD, ltps[i].url + len, EOF_L_ADDRESS);
      printf("LTP write: %s\n", cmd);

      if(!helper_write(hp, cmd, EOF_L_CMD+EOF_L_ADDRESS)) return 0;
   }

   return 1;
}
