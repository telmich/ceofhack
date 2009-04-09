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
#include "eof.h"   /* EOF */

int main()
{
   char input[EOF_L_CMD+EOF_L_ADDRESS+1];

   /* read init sequence: 1001 */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, "dummy-LTP cmd: %s\n", input);
   
   /* read the url */
   read(STDIN_FILENO, input, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, "dummy-LTP listens to url: %s\n", input);

   /* read command */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, "dummy-LTP received command and exits: %s\n", input);

   return 0;
}
