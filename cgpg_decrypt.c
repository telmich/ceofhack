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
 * Decrypt an incoming packet
 *
 */

#include <string.h>     /* strlen            */
#include <stdio.h>      /* printf            */
#include <gpgme.h>      /* gpgme             */
#include <locale.h>     /* locales           */
#include "ceofhack.h"   /* functions etc.    */

ssize_t cgpg_decrypt(char *msg, ssize_t msglen, char buf[], ssize_t bufsize)
{
   gpgme_data_t plaintext;
   gpgme_data_t encrypted;

   if(GPG_ERR_NO_ERROR != gpgme_data_new_from_mem(&encrypted, msg, msglen, 1)) return 0;
   if(GPG_ERR_NO_ERROR != gpgme_data_new(&plaintext)) return 0;
   if(GPG_ERR_NO_ERROR != gpgme_op_decrypt(gpg_context, encrypted, plaintext))
      return 0;
   if(GPG_ERR_NO_ERROR != gpgme_data_seek(plaintext, 0, SEEK_SET)) return 0;
   msglen = gpgme_data_read(plaintext, buf, bufsize);
   buf[msglen] = '\0';

   return msglen;
}
