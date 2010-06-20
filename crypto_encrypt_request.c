/*******************************************************************************
 *
 * 2010      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Initialise the crypto stuff
 *
 */

#include <stdio.h>      /* printf            */
#include <string.h>     /* memset()          */
#include <gpgme.h>      /* gpgme             */
#include <locale.h>     /* locales           */
#include "ceofhack.h"   /* functions etc.    */
#include "ceof.h"       /* functions etc.    */

void crypto_encrypt_request()
{

   /* read my key id */
   memset(opt.mykeyid, '\0', EOF_L_PIDLEN+1);
   if(!openreadclosestatic(opt.mykeyid, opt.mykeyidfile, EOF_L_KEYID)) {
      return 0;
   }

   printf(CEOF_MSG_CRYPTOPROMPT "My keyid: %s\n", opt.mykeyid);

   /* init ceof-crpyto */

   return 1;
}
