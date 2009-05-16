#ifndef EOF_H
#define EOF_H

/* Lengths */
#define EOF_L_CMD                4
#define EOF_L_KEYID              40
#define EOF_L_NICKNAME           128
#define EOF_L_MESSAGE            128
#define EOF_L_ADDRESS            128
#define EOF_L_GROUP              128
#define EOF_L_UI_INPUT           256
#define EOF_L_PKG_MAX            65536

/* commands */
#define EOF_CMD_TPS              "1000"
#define EOF_CMD_TPL_START        "1001"
#define EOF_CMD_TPL_STOP         "1002"

#define EOF_CMD_TPS_SENT         "2000"
#define EOF_CMD_TPS_NOT_SENT     "2001"
#define EOF_CMD_TPL_RECV         "2002"
#define EOF_CMD_TPL_LISTENING    "2003"

/* user interfaces: already implemented */
#define EOF_CMD_UI_ACK           "1100"
#define EOF_CMD_UI_REGISTER      "2100"

/* user interfaces: not implemented */
#define EOF_CMD_UI_FAILURE       "1101"
#define EOF_CMD_UI_EXITREQUEST   "1102"
#define EOF_CMD_UI_MSGRECEIVED   "1103"

#define EOF_CMD_UI_DEREGISTER    "2101"
#define EOF_CMD_UI_PEER_ADD      "2102"
#define EOF_CMD_UI_PEER_SEND     "2103"
#define EOF_CMD_UI_PEER_LIST     "2104"
#define EOF_CMD_UI_PEER_RENAME   "2105"
#define EOF_CMD_UI_PEER_SHOW     "2106"
#define EOF_CMD_UI_QUIT          "2199"


/* decoded packets from outside */
#define EOF_CMD_EXT_MESSAGE      "3000"
#define EOF_CMD_EXT_FORWARD      "3001"
#define EOF_CMD_EXT_MSGFWD       "3002"
#define EOF_CMD_EXT_DROP         "3003"

/* UI commands */
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

/* library functions */
int  eof_ui_connect();

#include <sys/types.h>           /* size_t   */
void eof_get_configdir(char buf[], size_t len);
void eof_get_ui_socketpath(char buf[], size_t len);
void eof_get_gpg_dir(char buf[], size_t len);
void eof_get_tp_dir(char buf[], size_t len);
int eof_cmd_2100(int sockfd);
int eof_cmd_2101(int sockfd);


#endif
