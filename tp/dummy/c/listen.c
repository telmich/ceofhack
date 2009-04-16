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

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "eof.h"   /* EOF */

int main()
{
   char input[EOF_L_PKG_MAX+1];
   ssize_t len;
   struct timespec ts;
   char *crypt = "-----BEGIN PGP MESSAGE-----\n\
Version: GnuPG v1.4.9 (GNU/Linux)\n\
\n\
hQIOAzz6ltMxvh7UEAf/Xy60gF+WHzgZNyflPb8seVn7KjSdA5ojkIpUjnsf4Xhc\n\
66PgvVrQwyiyYZ6KFs2f4naBwdSUTYEa/YL+7Tsc5el1ipdYxwdVOzD9Iac1XG9G\n\
QDeByA/UHk4CJj171I0CCJvIeuA7Bjd6JEpjCaNatxL1AGeLEAL4fv7dGzKYYwNc\n\
FvyaIDMWtbbY1VVHmPg1yv7he1y0bTAN/PrDmlvcE5t7YNpQGixbF4mVWtys4zLi\n\
ZIqculNyqd+BrBLB3tYbS7K/ixufYw2PdI4dWZ70bc0S0fK17gSjJI/l8DYIGV86\n\
pqeon/18JjNjj64yf86tf0TZZbDr1320QeLpKWrnUgf/e7ceFNySjJg/ZxX5jXU5\n\
eYYoFqM/h+uMBonssstQzpQcccinttR+zBcsaqbx6y8PxU/83Zu2pdhAHDcp3uo2\n\
dLitOKa5UDKBWbwxhym+l9MzNvrRTEE4ZyWnSuzWdPZBv39CkDC00pLb8AHCBWBU\n\
dBdCPPxznzPiA31aMiWRlmY+iZJ7oj2/4MTpSWfxLhVdGhos701xl8OuAzRIg0Xj\n\
9XWywzstNl7D3Gak4OqP+b7amzVLFHNjqcVMZ00qaz76Y+eO/hmPTlgzCrxtmxEm\n\
9ODn8w44RK9aiDdK6Mg5TnDZMENjLvDSWAfWznh34+Ah0dVnw7X3t7nTmljOjHMy\n\
I9JSARazAgS0KIQP8M/qYZMEOf22hBNYbNPBmfI3a7QQJGXqbGNTFPWqHtwu809W\n\
UQQpdMJCi/N7fhdVK2Rgws+fYN3qbX1XKG2jrxD1Yj0QbOU/KA==\n\
=pStt\n\
-----END PGP MESSAGE-----\n";

   /* read init sequence: 1001 */
   read(STDIN_FILENO, input, EOF_L_CMD);
   input[EOF_L_CMD] = '\0';
   fprintf(stderr, "dummy-LTP cmd: %s\n", input);
   
   /* read the url */
   read(STDIN_FILENO, input, EOF_L_ADDRESS);
   input[EOF_L_ADDRESS] = '\0';
   fprintf(stderr, "dummy-LTP listens to url: %s\n", input);

   /* wait some time and drop a "received packet" */
   ts.tv_sec  = 3;
   ts.tv_nsec = 0;
   nanosleep(&ts, NULL);

   len = write(STDOUT_FILENO, crypt, strlen(crypt));
   fprintf(stderr, "len=%lu\n", strlen(crypt));


   /* read commands */
   while(1) {
      len = read(STDIN_FILENO, input, EOF_L_PKG_MAX+1);
      if(len > EOF_L_PKG_MAX) {
         fprintf(stderr, "Packet too big (%lu)!\n", len);
         continue;
      }
      input[len] = '\0';
      fprintf(stderr, "dummy-LTP received command: %s (until first \\0)\n", input);

      if(!strncmp(input, EOF_CMD_TPL_STOP, EOF_L_CMD)) {
         fprintf(stderr, "dummy/c: Time to say goodbye...\n");
         return 0;
      }
   }

   return 0;
}
