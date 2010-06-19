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
 * Crypto related stuff
 *
 */

#ifndef CEOF_CRYPTO_H
#define CEOF_CRYPTO_H

/* constants */
#define CEOF_MSG_CRYPTO_NAME     "ceof-crypto"
#define CEOF_MSG_CRYPTO_PROMPT   CEOF_MSG_CRYPTO_NAME "> "
#define CEOF_MSG_CRYPTO_USAGE    CEOF_MSG_CRYPTO_PROMPT "Arguments: gpg-dir\n"

/* depending libs */
#include <gpgme.h>      /* gpgme             */
#include <eof.h>        /* EOF               */

/* structures */
#include <limits.h>              /* PATH_MAX                      */
struct crypto_options {
   char cryptohome[PATH_MAX+1];
   char gpg[PATH_MAX+1];
};

/* functions */
void crypto_usage();
int crypto_gpg_init();
int crypto_gpg_keyid_get(char *key, gpgme_key_t keyid[], char errmsg[EOF_L_MESSAGE]);

/* global vars */
extern struct crypto_options opt;

extern gpgme_ctx_t    gpg_context;
extern gpgme_data_t   gpg_encrypt;
extern gpgme_data_t   gpg_decrypt;



#endif
