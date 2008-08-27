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
 * Initialise the GPGME part
 *
 */

#include <stdio.h>      /* printf            */
#include <gpgme.h>      /* gpgme             */
#include <locale.h>     /* locales           */
#include "ceofhack.h"   /* functions etc.    */

gpgme_ctx_t gpg_context;

int gpg_init()
{
   char *p;
   gpgme_error_t gerr;
   
   setlocale (LC_ALL, "");
   p = (char *) gpgme_check_version(NULL);
   gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifdef LC_MESSAGES
   gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

   printf("gpg: Using version %s\n", p);

   gerr = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("Your gpgme library seems not to support OpenPGP!\n");
      return 0;
   }

   gerr = gpgme_new(&gpg_context);
   if(gerr != GPG_ERR_NO_ERROR) return 0;

   gerr = gpgme_ctx_set_engine_info(gpg_context,
                                    GPGME_PROTOCOL_OpenPGP,
                                    opt.gpg, opt.gpghome);
   if(gerr != GPG_ERR_NO_ERROR) return 0;

   return 1;
}
