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
 * Initialise commands in categories
 *
 */

#include <eof.h>
#include "crypto.h"   /* functions etc. */

int crypto_cmd_init()
{
   struct eof_cmd *newcmd;

   if(!eof_cmd_init(CEOF_CRYPTO_CMD_CATS)) return 0;

   /* ceof */
   if(!(newcmd = eof_cmd_create(EOF_CMD_CRYPTO_DEFAULT, crypto_cmd_default))) return 0;
   eof_cmd_cat_init(CEOF_CRYPTO_CAT_CEOF, newcmd);

//   if(!(newcmd = cmd_create(EOF_CMD_CRYPTO_ENCRYPT, cmd_1200))) return 0;
//   if(!cmd_cat_add(CEOF_CRYPTO_CAT_CEOF, newcmd)) return 0;

   return 1;
}
