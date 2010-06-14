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
#include "ceofhack.h"   /* context           */
#include "eof.h"        /* errmsg            */

int cgpg_keyid_get(char *key, gpgme_key_t keyid[], char errmsg[EOF_L_MESSAGE])
{
   if(GPG_ERR_NO_ERROR != gpgme_op_keylist_start(gpg_context, key, 0)) {
      eof_errmsg("gpgme_op_keylist_start failed");
      return 0;
   }
   if(GPG_ERR_NO_ERROR != gpgme_op_keylist_next(gpg_context, &keyid[0])) {
      eof_errmsg("gpgme_op_keylist_next failed");
      return 0;
   }
   if(GPG_ERR_NO_ERROR != gpgme_op_keylist_end(gpg_context)) {
      eof_errmsg("gpgme_op_keylist_end failed");
      return 0;
   }
   
   return 1;
}
