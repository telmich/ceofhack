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

#include <string.h>     /* strlen            */
#include <stdio.h>      /* printf            */
#include <gpgme.h>      /* gpgme             */
#include <locale.h>     /* locales           */
#include "ceofhack.h"   /* functions etc.    */

int cgpg_encrypt(char *nick, char *msg, char buf[], int len, char errmsg[EOF_L_MESSAGE])
{
//   gpgme_error_t gerr;
   gpgme_key_t keyid[2];
   gpgme_data_t plaintext;
   gpgme_data_t encrypted;
   char *p;

   /* retrieve keyid    */
   p = peer_keyid_get(nick);
   if(!p) {
      eof_errmsg("No key-ID registered");
      return 0;
   }

   keyid[1] = NULL;
   if(!cgpg_keyid_get(p, keyid)) {
      eof_errmsg("No gpg-key found");
      return 0;
   }
   printf("Key info: %s <%s>\n", keyid[0]->uids->name,  keyid[0]->uids->email);

   /* allocate buffer: non copying!   */
   if(GPG_ERR_NO_ERROR != gpgme_data_new_from_mem(&plaintext, msg, strlen(msg), 0))
      return 0;
   if(GPG_ERR_NO_ERROR != gpgme_data_new(&encrypted)) return 0;

   /* encrypt  buffer   */
   /* FIXME: remove GPGME_ENCRYPT_ALWAYS_TRUST and use trustlevels */
   if(GPG_ERR_NO_ERROR != gpgme_op_encrypt(gpg_context, keyid,
      GPGME_ENCRYPT_ALWAYS_TRUST, plaintext, encrypted)) {
      eof_errmsg("Encryption failed");
      return 0;
   }
   
   /* return result     */
   if(GPG_ERR_NO_ERROR != gpgme_data_seek(encrypted, 0, SEEK_SET)) {
      eof_errmsg("gpgme_data_seek");
      return 0;
   }
   len = gpgme_data_read(encrypted, buf, len);
   buf[len] = '\0';

   return len;
}
