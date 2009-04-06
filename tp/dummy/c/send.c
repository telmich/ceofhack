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
 * Dummy listener
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "eof.h"   /* EOF */

#define BIGBUF 65536

int main()
{
   char input[BIGBUF+1];
   char *eos;              /* end of size */
   int len;

   /* read init sequence: 1000 */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, "dummy-TP cmd: %s\n", input);
   
   /* read the url */
   read(STDIN_FILENO, input, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, "dummy-TP url: %s\n", input);

   /* read the rest...
    * FIXME: this is big buggy, should only read until
    * \n and then determine how much to read later on
    */
   len = read(STDIN_FILENO, input, BIGBUF);
   input[len] = '\0';

   eos = strchr(input, '\n');
   if(!eos) {
      printf("2001");
      return 1;
   } else {
      *eos = '\0';
   }

   fprintf(stderr, "dummy-TP size: %s\n", input);
   /* in theory, read the encrypted onion packet here */

   /* in this is indeed also buggy, though input is zero terminated..*/
   fprintf(stderr, "dummy-TP packet: %s\n", eos+1);

   return 0;
}
