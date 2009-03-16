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

char *cgpg_encrypt(char *nick, char *msg)
{
//   gpgme_error_t gerr;
   gpgme_key_t keyid[2];
   char *p;

   /* retrieve keyid    */
   p = peer_keyid_get(nick);
   if(!p) {
      printf("No key-ID registered for peer %s\n", nick);
      return 0;
   }

   keyid[1] = NULL;
   if(!cgpg_keyid_get(p, keyid)) {
      printf("No gpg-key found for peer %s\n", nick);
      return 0;
   }
   printf("Using key %s <%s>\n", keyid[0]->uids->name,  keyid[0]->uids->email);
   /* allocate buffer   */
   /* encrypt  buffer   */
   /* return result     */

   return NULL;
}
