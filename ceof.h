/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * The clean internal ceof header
 *
 */

#ifndef CEOF_H
#define CEOF_H

/* constants */
#define CEOF_MSG_NAME            "ceofhack"
#define CEOF_MSG_PROMPT          CEOF_MSG_NAME "> "
#define CEOF_MSG_VERSION         CEOF_MSG_PROMPT "Version 0.5\n"
#define CEOF_MSG_STARTED         CEOF_MSG_PROMPT "Started. Please enter commands.\n"

enum {
   CEOF_EX_RUNS = 0,
   CEOF_EX_RUNS_ERR,
   CEOF_EX_CONFIG,
   CEOF_EX_ID,
   CEOF_EX_HELPER,
   CEOF_EX_GPG,
   CEOF_EX_SIGNALS,
   CEOF_EX_CMD,
   CEOF_EX_TP,
   CEOF_EX_PEER,
   CEOF_EX_UI,
   CEOF_EX_POLL,
   CEOF_EX_NOWAY
};

/* functions */
void ceof_banner(char *);

#endif
