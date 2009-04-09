#ifndef THIS_IS_AN_UGLY_CEOF_HACK
#define THIS_IS_AN_UGLY_CEOF_HACK

/****************** Includes  */
#include <poll.h>    /* pollfd */

#include "eof.h"     /* the clean library header   */
#include "shcl.h"    /* small helper c library     */

/****************** Defines  */
/* ugly hack to satisfy -Wextra */
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#else
# define UNUSED(x) x
#endif

/* the library version is not yet used */
#define LIBEOF_VERSION "E.O.F"


/*
 * internal limits
 */

#define EOF_L_GUI       256
#define EOF_L_TPA       256      /* max available tp (all)        */
#define EOF_L_TPL       256      /* max available tp listener     */
#define MAX_RCP         1        /* gpgme recipients              */
#define BIGBUF          65536
#define MAX_COMM        256      /* maximum number of communication
                                  * channels contains stdin, listen
                                  * sockets and outgoing sockets
                                  */
#define HACK_CMD_CAT    32       /* number of command categories:
                                  * - Sending transport protocols (TPS)
                                  * - Listening transport protocols (TPL)
                                  * - user interfaces (UI)
                                  * uses an unsigned long it -> 32 is maximum!
                                  */
#define EOF_L_PEER_INPUT  256    /* FIXME: HACKs */

/* parts of the pipe array _we_ use */
#define HP_READ            0
#define HP_WRITE           3

/* UI commands */
#define UI_QUIT      "/quit"
#define UI_PEER_ADD  "/peer add"
#define UI_PEER_LIST "/peer list"
#define UI_PEER_SEND "/peer send"
#define UI_HELP      "/help"

/* TP commands */
#define EOF_TPCMD_INIT_LTP     "1001"

/****************** Structures  */
struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
   char keyid[EOF_L_KEYID+1];
};

struct peers {
   struct peer peer;
   struct peers *next;
};

/* user interface commands */
struct ui_cmd {
   char *name;
   int (*handle)(char *);
   struct ui_cmd *next;
};

/* EOF commands */
struct cmd {
   char *num;
   int (*handle)(int []);
   struct cmd *next;
};

/* EOF commands categories */
struct cmd_cat {
   unsigned long cat;         /* no more than 32 categories */
   struct cmd *next;          /* pointer to first cmd       */
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

#include <sys/types.h>           /* POSIX for pid_t               */
struct helper {                  /* for the subprojects           */
   pid_t pid;                    /* process id                    */
   int fds[4];                   /* file deskriptors used by poll */
   char path[PATH_MAX+1];        /* absolute path                 */
   int (*handle)(int []);        /* pointer to the handler        */
   int (*exit)(int []);          /* pointer to the exit function  */
};

struct tp {                      /* transport protocols           */
   char scheme[EOF_L_ADDRESS+1]; /* type of protocol: tcp, ...    */
   struct cconfig *listen;       /* non-NULL if available         */
   struct cconfig *send;         /* non-NUll if available         */
};

struct tpl {                     /* listening transport protocols */
   char url[EOF_L_ADDRESS+1];    /* tcp:where-are-you             */
   struct cconfig *listen;       /* program that can decode stuff */
};

/* cmd categories, use in other places as well, need to be '&'-able  */
enum {
   TPN = 0x0,     /* TP nothing / none    */
   TPL = 0x1,     /* TP listen            */
   TPS = 0x2      /* TP sending           */
};

/* hacking cconfig lib into ceofhack */
struct cconfig {
   char path[PATH_MAX+1];     /* full path         */
   int noe;                   /* number of entries */
   struct cconfig *entries;   /* directory entries */
};

/****************** Global variables  */
extern struct pollfd    pfd[MAX_COMM];
extern struct peers     plist;
extern struct options   opt;

/* helper subsystem */
extern struct helper    chp[MAX_COMM];
extern int              chp_cnt;

/* builtin user interface */
extern struct ui_cmd    ui_cmds;

/* transport */
extern struct tp        tpa[EOF_L_TPA];
extern int              tpa_cnt;
extern struct tpl       tpls[EOF_L_TPL];
extern int              tpls_cnt;
extern struct cconfig   tp_tree;

/* commands */
extern struct cmd_cat   cmdlist[HACK_CMD_CAT];
extern int              cmdlist_cnt;

/* gpgme */
#include <gpgme.h>      /* gpgme             */
extern gpgme_ctx_t    gpg_context;
extern gpgme_data_t   gpg_encrypt;
extern gpgme_data_t   gpg_decrypt;

/****************** Functions  */
int forkexecpipe(struct helper *hp);
void fd_to_poll();
int signals_init();
void signal_child(int sig);

int helper_init();
int helper_new();
int helper_fdonly(int fd, int (*handle)(int []), int (*exit)(int []));
struct helper *helper_exec(char *path, int (*handle)(int []), int (*exit)(int []));
int helper_write(struct helper *hp, char *buf, int len);
struct helper *helper_find_by_pid(pid_t pid);

/* sample user interface, hardcoded into ceofhack for now */
int ui_cmds_init();
int ui_cmd_add(char *name, int (*handle)(char *));
struct ui_cmd *ui_cmd_check(char *string);
int ui_help(char *);
int ui_quit(char *);

int ui_cmd_read(int fd[]);
int peer_input(int fd[]);

void check_input();

int peers_init();
int peer_add(char *);
int peer_list(char *);
int peer_send(char *);
struct peer *peer_findbyname(char *name);
char *peer_keyid_get(char *nick);
char *peer_addr_get(char *name);

int cgpg_init();
int cgpg_encrypt(char *nick, char *msg, char buf[], int len);
int cgpg_keyid_get(char *key, gpgme_key_t keyid[]);

int config_init();

int tp_init();
int tp_add_available(char *name, struct cconfig entry);
int tp_listen_add(char *name, struct cconfig entry);
int tp_listen_init();
int tp_listen_read(int fd[]);
int tp_scheme_len(char *url);
struct cconfig *tp_available(char *url, int type);
int tp_send(char *nick, char *msg);
int tp_send_wait(int fds[]);


int cconfig_tree(struct cconfig *cg);
struct cconfig *cconfig_find_fn(char *fn, struct cconfig src, struct cconfig *dst);
int cconfig_tree_dump(struct cconfig tree, int level);
int cconfig_entries_get(struct cconfig tree, struct cconfig *next, int *state);
char *cconfig_entry_fn(struct cconfig *entry);

/* shcl */
int openreadclosestatic(char buf[], char *fn, int len);
ssize_t write_all(int fd, const void *buf, size_t count);

/* commands */
int cmd_handle(int type, char data[], int fd[]);
int cmd_init();
int cmd_cat_create(unsigned long);
struct cmd *cmd_create(char num[], int (*handle)(int []));
int cmd_2000(int []);
int cmd_cat_add(unsigned long, struct cmd *cmd);
struct cmd_cat *cmd_cat_find(unsigned long cat);

#endif
