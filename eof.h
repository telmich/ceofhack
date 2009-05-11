#ifndef EOF_H
#define EOF_H

/* Lengths */
#define EOF_L_CMD       4
#define EOF_L_KEYID     40
#define EOF_L_NICKNAME  128
#define EOF_L_MESSAGE   128
#define EOF_L_ADDRESS   128
#define EOF_L_CHANNEL   128
#define EOF_L_UI_INPUT  256
#define EOF_L_PKG_MAX   65536

/* areas / categories / components */
#define EOF_C_TP         0x01       /* transport protocols */


/* commands */
#define EOF_CMD_TPS              "1000"
#define EOF_CMD_TPL_START        "1001"
#define EOF_CMD_TPL_STOP         "1002"
#define EOF_CMD_TPS_SENT         "2000"
#define EOF_CMD_TPS_NOT_SENT     "2001"
#define EOF_CMD_TPL_RECV         "2002"
#define EOF_CMD_TPL_LISTENING    "2003"

/* decoded packets from outside */
#define EOF_CMD_EXT_MESSAGE      "3000"
#define EOF_CMD_EXT_FORWARD      "3001"
#define EOF_CMD_EXT_MSGFWD       "3002"
#define EOF_CMD_EXT_DROP         "3003"

/* UI commands */
#define EOF_UI_QUIT      "/quit"
#define EOF_UI_PEER_ADD  "/peer add"
#define EOF_UI_PEER_LIST "/peer list"
#define EOF_UI_PEER_SEND "/peer send"
#define EOF_UI_HELP      "/help"

#endif
