#ifndef THIS_IS_AN_UGLY_CEOF_HACK
#define THIS_IS_AN_UGLY_CEOF_HACK

#include <poll.h>    /* pollfd */

/* the library version is not yet used */

#define LIBEOF_VERSION "E.O.F"

/* FIXME: HACKs */
#define EOF_L_PEER_INPUT  256

/*
 * those values are from the current EOF specs
 */

/* gui2user */
#define EOF_L_GUI       256

/* basics */
#define EOF_L_NICKNAME  128
#define EOF_L_MESSAGE   128
#define EOF_L_ADDRESS   128
#define EOF_L_KEYID      40

#define EOF_L_TP_AVAIL  256      /* max available tp              */
#define EOF_L_LTP       256      /* max available tp listener     */

#define SIZE 1024
#define MAX_RCP 1
#define BIGBUF 65536

#define MAX_COMM 64 /* maximum number of communication channels
                          contains stdin, listen sockets
                          and outgoing sockets */

/* FIXME: need to listen on stdin and ipv4 socket  --> STATIC */
#define HP_LAST 2

/* commands */
#define UI_QUIT      "/quit"
#define UI_PEER_ADD  "/peer add"
#define UI_PEER_LIST "/peer list"
#define UI_PEER_SEND "/peer send"
#define UI_HELP      "/help"

/* user commands */

/* Structures */
struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
   char keyid[EOF_L_KEYID+1];
};

struct peers {
   struct peer peer;
   struct peers *next;
};

struct cmd {
   char *name;
   int (*handle)(char *);
   struct cmd *next;
};

/* further structs with external dependencies */
#include <limits.h>              /* PATH_MAX                      */
struct options {
   char home[PATH_MAX+1];
   char ceofhome[PATH_MAX+1];
   char gpghome[PATH_MAX+1];
   char gpg[PATH_MAX+1];
   char tphome[PATH_MAX+1];
};

#include <sys/types.h>           /* FIXME: posix correct header?) */
struct helper {                  /* for the subprojects           */
   pid_t pid;                    /* process id                    */
   int fds[2];                   /* file deskriptors used by poll */
   char *path;                   /* path relative to config dir   */
   int (*handle)(int []);        /* pointer to the handler        */
   int (*exit)(int []);          /* pointer to the exit function  */
};

struct tp {                      /* transport protocols           */
   char scheme[EOF_L_ADDRESS+1]; /* type of protocol: tcp, ...    */
   struct cconfig *listen;       /* non-NULL if available         */
   struct cconfig *send;         /* non-NUll if available         */
};

struct ltp {                     /* listening transport protocols */
   char url[EOF_L_ADDRESS+1];    /* tcp://where-are-you           */
   struct tp *handler;           /* who can decode stuff          */
};

enum {
   TP_NOTHING = 0,
   TP_LISTEN = 1,
   TP_SEND   = 2
};

/* hacking cconfig lib into ceofhack */
struct cconfig {
   char path[PATH_MAX+1];     /* full path         */
   int noe;                   /* number of entries */
   struct cconfig *entries;   /* directory entries */
};

/****************** Global variables  */
extern struct helper    chp[MAX_COMM];
extern struct pollfd    pfd[MAX_COMM];
extern struct cmd       cmds;
extern struct peers     plist;
extern struct options   opt;
extern int              chp_cnt;

/* transport */
extern struct tp        tps[EOF_L_TP_AVAIL];
extern int              tps_cnt;
extern struct cconfig   tp_tree;

/* gpgme */
#include <gpgme.h>      /* gpgme             */
extern gpgme_ctx_t    gpg_context;
extern gpgme_data_t   gpg_encrypt;
extern gpgme_data_t   gpg_decrypt;

/* Functions */
int forkexecpipe(char *path, struct helper *hp);
void fd_to_poll();
int signals_init();
void signal_child(int sig);

int helper_new();
int helper_fdonly(int fd, int (*handle)(int []), int (*exit)(int []));
int helper_exec(char *path, int (*handle)(int []), int (*exit)(int []));

int cmds_init();
int cmd_add(char *name, int (*handle)(char *));
struct cmd *cmd_check(char *string);

int ui_help(char *);
int ui_quit(char *);

int user_input(int fd[]);
int peer_input(int fd[]);

void check_input();

int peers_init();
int peer_add(char *);
int peer_list(char *);
int peer_send(char *);
struct peer *peer_findbyname(char *name);
char *peer_keyid_get(char *nick);

int cgpg_init();
int cgpg_encrypt(char *nick, char *msg, char buf[], int len);
int cgpg_keyid_get(char *key, gpgme_key_t keyid[]);

int config_init();

int tp_init();
int tp_add_available(char *name, struct cconfig entry);
int tp_add_listener(char *name, struct cconfig entry);

//int cconfig_tree(char *path, struct cconfig *cg);
int cconfig_tree(struct cconfig *cg);
struct cconfig *cconfig_find_fn(char *fn, struct cconfig src, struct cconfig *dst);
int cconfig_tree_dump(struct cconfig tree, int level);
int cconfig_entries_get(struct cconfig tree, struct cconfig *next);
char *cconfig_entry_fn(struct cconfig *entry);

#endif
