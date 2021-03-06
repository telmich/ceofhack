/*******************************************************************************
 *
 * 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
#include "ceof.h"       /* functions etc.    */

gpgme_ctx_t    gpg_context;
gpgme_data_t   gpg_encrypt;
gpgme_data_t   gpg_decrypt;

int crypto_gpg_init()
{
   char *p;
   gpgme_error_t gerr;
   
   setlocale (LC_ALL, "");
   p = (char *) gpgme_check_version(NULL);
   gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifdef LC_MESSAGES
   gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif

   printf(CEOF_MSG_CRYPTOPROMPT "Version %s\n", p);

   gerr = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf(CEOF_MSG_CRYPTOPROMPT "Your gpgme library seems not to support OpenPGP!\n");
      return 0;
   }

   gerr = gpgme_new(&gpg_context);
   if(gerr != GPG_ERR_NO_ERROR) return 0;

   gerr = gpgme_ctx_set_engine_info(gpg_context,
                                    GPGME_PROTOCOL_OpenPGP,
                                    opt.gpg, opt.cryptohome);
   if(gerr != GPG_ERR_NO_ERROR) return 0;
   gpgme_set_armor(gpg_context, 0);

   /* FIXME: ascii armor only for testing */
   gpgme_set_armor(gpg_context, 1);

//   write passwd retrieval!
//   gpgme_set_passphrase_cb(gpg_context, gpg_getpwd, NULL);

   return 1;
}
