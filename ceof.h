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

#include "version.h"
#include "eof.h"

/* constants */
#define CEOF_MSG_NAME            "ceofhack"
#define CEOF_MSG_PROMPT          CEOF_MSG_NAME "> "
#define CEOF_MSG_VERSION         CEOF_MSG_PROMPT "Version " CEOF_VERSION "\n"
#define CEOF_MSG_STARTED         CEOF_MSG_PROMPT "Started, waiting for connections.\n"
#define CEOF_MSG_UINAME          "ui"
#define CEOF_MSG_UIPROMPT        CEOF_MSG_UINAME "> "
#define CEOF_MSG_TPNAME          "tp"
#define CEOF_MSG_TPPROMPT        CEOF_MSG_TPNAME "> "
#define CEOF_MSG_CRYPTONAME      "crypto"
#define CEOF_MSG_CRYPTOPROMPT    CEOF_MSG_CRYPTONAME "> "

enum {
   CEOF_EX_RUNS = 0,
   CEOF_EX_RUNS_ERR,
   CEOF_EX_CONFIG,
   CEOF_EX_ID,
   CEOF_EX_HELPER,
   CEOF_EX_CRYPTO,
   CEOF_EX_SIGNALS,
   CEOF_EX_CMD,
   CEOF_EX_TP,
   CEOF_EX_PEER,
   CEOF_EX_UI,
   CEOF_EX_POLL,
   CEOF_EX_EOFS,
   CEOF_EX_NOWAY
};

/* structures */
#include <limits.h>              /* PATH_MAX                      */
struct options {
   char home[PATH_MAX+1];
   char cryptohome[PATH_MAX+1];
   char tphome[PATH_MAX+1];
   char uisocket[PATH_MAX+1];
   char pidfile[PATH_MAX+1];
   char mykeyidfile[PATH_MAX+1];
   char gpg[PATH_MAX+1];

   char mykeyid[EOF_L_KEYID+1];
   pid_t pid;

};


/* functions */
void ceof_banner(char *);

/* crypto */
int crypto_init();
int crypto_gpg_init();

/* eof subsystem handler */
int eofs_init();
//int eofs_iterate(int , struct eofs_list **);

#endif
