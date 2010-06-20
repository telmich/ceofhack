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
 * Create a partial onion containing a message and drop command
 *
 */

#include <string.h>        /* memset, str* */
#include <eof.h>

void onion_partial_create(char cmd[], char id[], char addr[], char group[], char msg[], char pkg[])
{
   int offset = 0;

   strncpy(&pkg[offset], cmd, EOF_L_CMD);       offset += EOF_L_CMD;
   strncpy(&pkg[offset], id,  EOF_L_ID);        offset += EOF_L_ID;
   strncpy(&pkg[offset], addr, EOF_L_ADDRESS);  offset += EOF_L_ADDRESS;
   strncpy(&pkg[offset], group, EOF_L_GROUP);   offset += EOF_L_GROUP;
   strncpy(&pkg[offset], msg, EOF_L_MESSAGE);   offset += EOF_L_MESSAGE;
}
