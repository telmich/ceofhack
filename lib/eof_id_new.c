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
//   static size_t len = strlen(convert);
   unsigned long cur = eof_id;
   int i, index;

   /* convert eof_id to a-z,A-Z,0-9 
   
i = 1 >  /64                  = (2^6)^1 = 2^6 
i = 2 >  /64^2 = 4096         = (2^6)^2 = 2^12
i = 3 >  /64^3 = 262144       = (2^6)^3 = 2^18

      base 62:

         a * 62^0 + b * 62^1 + c * 62^3 ... x * 62^(EOF_L_ID-1)


         len = 64;      convert     num % 64 =     num / 64 =

   0        0           0                 0           0
   1        0           1                 1           0
   16       0           f                16           0
   65                   11
   72       1           1a               10           1
   190      3           34                4           3
   4096

   "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!";
             9                                                    63
   
   64 = 10
   65 = 11

   4160 = 65 * 64 = 64 * 64 + 64 = 100
   4161 = 65 * 64, rest 1  = 64 * 64 + 64, rest 1 = 101

   3 stellen: 64^0 64^1 64^2, maximal: (64^3)-1

      4161/64^2 = 1


   0
   1
   .
   .
   9
   

      >> 1 = 2, 2 = 4, 3 = 8, 4 = 16, 5 = 32, 6 = 64

      buf[EOF_L_ID-1] = cur >> (EOF_L_ID-1)*6
      buf[EOF_L_ID-2]
      ...
      buf[0]

   fails at 4160, because 4160/64 = 65 ...

   einmal / 64 



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
