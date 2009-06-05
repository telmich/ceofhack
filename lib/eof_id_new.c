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
 * Return a new ID
 *
 */

#include <string.h>     /* strlen            */
#include <stdio.h>      /* printf            */
#include "eof.h"        /* EOF*              */


int eof_id_new(char buf[EOF_L_ID])
{
   char *convert = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!";
   unsigned long cur = eof_id;
   int i, index;

   /* convert decimal to base 64:

      - Use highest base64 number: 64^(EOF_L_ID-1),
      - divide the current number by it: cur/64^(EOF_L_ID-1)
      - with shifting this results to cur >> i*6, which is the index
      - substract the part that could be expressed: cur -= index * (1 << i*6);
      - assign the character specified by index to the buffer element
      - continue while EOF_L_ID-n > 0
      - the last element can be choosen directly, because the number ("cur")
        may only contain up to the maximum auf (64^0)-1
   
      i = 1 >  /64                  = (2^6)^1 = 2^6 
      i = 2 >  /64^2 = 4096         = (2^6)^2 = 2^12
      i = 3 >  /64^3 = 262144       = (2^6)^3 = 2^18
      ...

   "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!";

   */

   for(i=EOF_L_ID-1; i > 0; i--) {
      index = cur >> i*6;
      if(index > 64) {
         fprintf(stderr, "Ohh, the eof_id is too big (%lu)! resetting it\n", eof_id);
         eof_id = 0;
         index = 0;
      }
//      printf("%lu-%lu: id[%d] = %d \n", cur, (long) 1 << i*6, i, index);
      cur -= index * (1 << i*6);
      buf[i] = convert[index];
   }
//   printf("%lu, idx=%d\n", cur, index);
   buf[0] = convert[cur];

   ++eof_id;

   return 1;
}
