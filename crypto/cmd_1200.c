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
 * React on incoming 1200 command
 *
 */

#include <stdio.h>      /* printf()          */
#include <stdlib.h>     /* strtoul           */
#include <string.h>     /* memset            */
#include <eof.h>        /* functions etc.    */

#include "crypto.h"

int cmd_1200(int fd[])
{
   char keyid[EOF_L_KEYID+1];
   char size[EOF_L_SIZE+1];
   char text[EOF_L_PKG_MAX+1];
   int len;

   memset(keyid, 0, EOF_L_KEYID+1);
   memset(size, 0, EOF_L_SIZE+1);
   memset(text, 0, EOF_L_PKG_MAX+1);

   if(!eof_va_read(fd[EOF_CMD_READ], 2,   EOF_L_KEYID, keyid,
                                          EOF_L_SIZE, size)) {
      perror("cmd_1200/eof_va_read");
      return 0;
   }

   fprintf(stderr, CEOF_MSG_CRYPTO_PROMPT "1200: %s, %s\n", keyid, size);

   len = strtoul(size, NULL, 10);
   /* FIXME: be more smart */
   if(len > EOF_L_PKG_MAX) return 0;

   if(!eof_va_read(fd[EOF_CMD_READ], 1, len, text)) {
      perror("cmd_1200/eof_va_read");
      return 0;
   }
   /* FIXME: may have \0 way before... */
   fprintf(stderr, "Text: %s\n", text);

   return 1;
}
