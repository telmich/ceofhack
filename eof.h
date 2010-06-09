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
 * Library header
 *
 */


#ifndef EOF_H
#define EOF_H

/* Lengths */
#define EOF_L_CMD                4
#define EOF_L_SIZE               6
#define EOF_L_ID                 6
#define EOF_L_KEYID              40
#define EOF_L_NICKNAME           128
#define EOF_L_MESSAGE            128
#define EOF_L_ADDRESS            128
#define EOF_L_GROUP              128
#define EOF_L_UI_INPUT           256
#define EOF_L_PKG_ONION          EOF_L_CMD+EOF_L_ID+EOF_L_ADDRESS+EOF_L_GROUP+EOF_L_MESSAGE
#define EOF_L_PKG_MAX            65536

/* commands */
#define EOF_CMD_TPS              "1000"
#define EOF_CMD_TPL_START        "1001"
#define EOF_CMD_TPL_STOP         "1002"

#define EOF_CMD_TPS_DEFAULT      "20xx"
#define EOF_CMD_TPS_SENT         "2000"
#define EOF_CMD_TPS_NOT_SENT     "2001"
#define EOF_CMD_TPL_RECV         "2002"
#define EOF_CMD_TPL_LISTENING    "2003"

/* queue/id */
#define EOF_QUEUE_ID_CHARS       "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!"

/* user interfaces: already implemented */
#define EOF_CMD_UI_ACK           "1100"
#define EOF_CMD_UI_FAIL          "1101"
#define EOF_CMD_UI_EXITREQUEST   "1102"
#define EOF_CMD_UI_MSGRECEIVED   "1103"
#define EOF_CMD_UI_PEER_LISTING  "1104"
#define EOF_CMD_UI_PEER_INFO     "1105"

#define EOF_CMD_UI_DEFAULT       "21xx"
#define EOF_CMD_UI_REGISTER      "2100"
#define EOF_CMD_UI_DEREGISTER    "2101"
#define EOF_CMD_UI_PEER_ADD      "2102"
#define EOF_CMD_UI_PEER_SEND     "2103"
#define EOF_CMD_UI_PEER_RENAME   "2104"
#define EOF_CMD_UI_PEER_SHOW     "2105"
#define EOF_CMD_UI_PEER_LIST     "2106"
#define EOF_CMD_UI_QUIT          "2199"


/* decoded packets from outside */
#define EOF_CMD_ONION_DROP         "3000"
#define EOF_CMD_ONION_FORWARD      "3001"
#define EOF_CMD_ONION_MSG_DROP     "3002"
#define EOF_CMD_ONION_MSG_FORWARD  "3003"
#define EOF_CMD_ONION_ACK          "3004"

/* UI commands */
#define EOF_UI_EXIT              "/exit"
#define EOF_UI_QUIT              "/quit"
#define EOF_UI_PEER_ADD          "/peer add"
#define EOF_UI_PEER_LIST         "/peer list"
#define EOF_UI_PEER_SEND         "/peer send"
#define EOF_UI_HELP              "/help"

/* environment variables */
#define EOF_ENV_UI_SOCKET        "EOF_UI_SOCKET"
#define EOF_ENV_EOF_HOME         "EOF_HOME"
#define EOF_ENV_HOME             "HOME"

/* paths */
#define EOF_P_SLASH              "/"
#define EOF_P_CONFIGDIR          ".ceof"
#define EOF_P_UI_SOCKET          EOF_P_SLASH "ui" EOF_P_SLASH "socket"
#define EOF_P_GPG_DIR            EOF_P_SLASH "gpg"
#define EOF_P_TP_DIR             EOF_P_SLASH "tp"
#define EOF_P_PIDFILE            EOF_P_SLASH "pid"

/* macros */
#define eof_errmsg(msg) (snprintf(errmsg, EOF_L_MESSAGE, msg))

/* global library variables */
extern unsigned long eof_id;

/* library functions: generic */
#include <sys/types.h>           /* size_t   */
void eof_get_configdir(char buf[], size_t len);
void eof_get_gpg_dir(char buf[], size_t len);
void eof_get_tp_dir(char buf[], size_t len);
void eof_get_pidfile(char buf[], size_t len);
int eof_ui_register(int sockfd, char id[]);
int eof_ui_deregister(int sockfd);


/* low level, normally not used directly */
int eof_va_read(int sockfd, int nof, ...);
int eof_va_write(int sockfd, int nof, ...);
int eof_id_init();
int eof_id_new(char buf[]);

/* library functions: user interfaces (low level)*/
void eof_get_ui_socketpath(char buf[], size_t len);
int eof_ui_connect();

/* library functions: user interfaces (high level)*/
int eof_ui_init(char id[]);
int eof_ui_peer_add(int sockfd, char errmsg[EOF_L_MESSAGE], char nick[EOF_L_NICKNAME],
                    char add[EOF_L_ADDRESS], char keyid[EOF_L_KEYID]);
int eof_ui_peer_list(int sockfd, char errmsg[EOF_L_MESSAGE], char **res);
int eof_ui_peer_send(int sockfd, char errmsg[EOF_L_MESSAGE],
                     char nick[EOF_L_NICKNAME], char msgtxt[EOF_L_MESSAGE]);
int eof_ui_peer_rename(int sockfd, char errmsg[EOF_L_MESSAGE],
                     char oldnick[EOF_L_NICKNAME], char newnick[EOF_L_NICKNAME]);
int eof_ui_peer_show(int sockfd, char errmsg[EOF_L_MESSAGE],
                     char nick[EOF_L_NICKNAME], char keyid[EOF_L_KEYID],
                                          char **addrs);
int eof_ui_quit(int sockfd);

/* queue */

#endif
