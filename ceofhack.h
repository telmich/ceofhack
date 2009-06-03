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

#define EOF_L_PIDLEN    32       /* maximum length of a pid       */
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
#define EOF_L_MAX_UI_WAIT  32    /* FIXME: HACKs */

/* parts of the pipe array _we_ use */
#define HP_READ            0
#define HP_EXT_WRITE       1
#define HP_EXT_READ        2
#define HP_WRITE           3
#define HP_FDCNT           4     /* number of fds used by helper structure */

/****************** Structures  */
struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
   char keyid[EOF_L_KEYID+1];
   struct peer *next;
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
   struct cmd *def;           /* pointer to default handler */
};

/* further structs with external dependencies */
#include <limits.h>              /* PATH_MAX                      */
struct options {
   char home[PATH_MAX+1];
   char gpghome[PATH_MAX+1];
   char tphome[PATH_MAX+1];
   char uisocket[PATH_MAX+1];
   char pidfile[PATH_MAX+1];
   pid_t pid;

   char gpg[PATH_MAX+1];
};

#include <sys/types.h>           /* POSIX for pid_t               */
struct helper {                  /* for the subprojects           */
   pid_t pid;                    /* process id                    */
   int fds[HP_FDCNT];            /* file deskriptors used by poll */
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

/* FIXME: needed? */
/* cmd categories, use in other places as well, need to be '&'-able  */
enum {
   TPN = 0x0,     /* TP nothing / none    */
   TPL = 0x1,     /* TP listen            */
   TPS = 0x2,     /* TP sending           */
   EXR = 0x4,     /* Externally received  */
   UIL = 0x8      /* UI listening         */
};

/* incoming data  categories */
#define EOF_I_TP                 0x01       /* transport protocols */
#define EOF_I_UI                 0x02       /* user interfaces     */


/* hacking cconfig lib into ceofhack */
struct cconfig {
   char path[PATH_MAX+1];     /* full path         */
   int noe;                   /* number of entries */
   struct cconfig *entries;   /* directory entries */
};

/****************** Global variables  */
extern struct pollfd    pfd[MAX_COMM];
extern struct peer      plist;
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
/* generic */
int config_init();
int forkexecpipe(struct helper *hp);
void fd_to_poll(int *);
int signals_init();
void signal_child(int sig);
void ceof_exit(int tmp);
void ceof_banner();
int ceof_runs();

/* helper */
int helper_init();
int helper_new();
void helper_check_input(int possible, int *have_data);
void helper_disable(struct helper *hp);
int helper_fdonly(int in, int out, int (*handle)(int []), int (*exit)(int []));
struct helper *helper_exec(char *path, int (*handle)(int []), int (*exit)(int []));
int helper_write(struct helper *hp, char *buf, int len);
struct helper *helper_find_by_pid(pid_t pid);
struct helper *helper_find_by_fd(int num, int fd);
struct helper *helper_find_by_handle(int *last, int (*handle)(int []));
int helper_signal(struct helper *hp, int sig);
int helper_signal_all(int sig);

/* sample user interface, hardcoded into ceofhack for now */
int ui_cmds_init();
int ui_cmd_add(char *name, int (*handle)(char *));
struct ui_cmd *ui_cmd_check(char *string);
int ui_help(char *);
int ui_quit(char *);
int ui_cmd_read(int fd[]);


/* peers */
int peer_init();
int peer_add(char nick[EOF_L_NICKNAME], char addr[EOF_L_ADDRESS], char keyid[EOF_L_KEYID]);
int peer_rename(char oldnick[EOF_L_NICKNAME], char newnick[EOF_L_NICKNAME],
                char errmsg[EOF_L_MESSAGE]);
int peer_show(int fd[]);
struct peer *peer_new();
int peer_list(int fd);
int peer_send(char nick[EOF_L_NICKNAME+1], char msg[EOF_L_MESSAGE+1],
              char errmsg[EOF_L_MESSAGE+1]);
struct peer *peer_findbyname(char *name);
char *peer_keyid_get(char *nick);
char *peer_addr_get(char *name);
int peer_input(int fd[]);

/* crypto via gpg(me) */
int cgpg_init();
int cgpg_encrypt(char *nick, char *msg, char buf[], int len, char errmsg[EOF_L_MESSAGE]);
ssize_t cgpg_decrypt(char *msg, ssize_t msglen, char buf[], ssize_t bufsize);
int cgpg_keyid_get(char *key, gpgme_key_t keyid[], char errmsg[EOF_L_MESSAGE]);

/* transport protocols */
int tp_init();
int tp_add_available(char *name, struct cconfig entry);
int tp_listen_add(char *name, struct cconfig entry);
int tp_listen_init();
int tp_listen_read(int fd[]);
int tp_scheme_len(char *url);
struct cconfig *tp_available(char *url, int type);
int tp_send(char *nick, char *msg, int len, char errmsg[EOF_L_MESSAGE]);
int tp_send_wait(int fds[]);
char *tp_getscheme(char *url);

/* cconfig */
int cconfig_tree(struct cconfig *cg);
struct cconfig *cconfig_find_fn(char *fn, struct cconfig src, struct cconfig *dst);
int cconfig_tree_dump(struct cconfig tree, int level);
int cconfig_entries_get(struct cconfig tree, struct cconfig *next, int *state);
char *cconfig_entry_fn(struct cconfig *entry);

/* shcl */
int openreadclosestatic(char buf[], char *fn, int len);
ssize_t write_all(int fd, const void *buf, size_t count);
ssize_t read_all(int fd, void *buf, size_t count);

/* commands */
int cmd_handle(unsigned long cat, int fd[], char data[]);
int cmd_init();
int cmd_cat_create(unsigned long cat, struct cmd *);
struct cmd *cmd_create(char num[], int (*handle)(int []));
struct cmd *cmd_cat_default_cmd(unsigned long cat);

int cmd_2000(int []);
int cmd_2002(int []);
int cmd_2003(int []);
int cmd_20xx(int []);

/* UI */
int cmd_1103(char nick[EOF_L_NICKNAME], char msgtxt[EOF_L_MESSAGE]);
int cmd_2100(int []);
int cmd_2101(int []);
int cmd_2102(int []);
int cmd_2103(int []);
int cmd_2104(int []);
int cmd_2105(int []);
int cmd_2106(int []);
int cmd_2199(int []);
int cmd_21xx(int []);

//int cmd_3000(int []);
int cmd_cat_add(unsigned long, struct cmd *cmd);
struct cmd_cat *cmd_cat_find(unsigned long cat);
struct cmd *cmd_find_in_cat(unsigned long cat, char cmd[]);

/* user interfaces */
int ui_init();
int ui_handle(int []);
int ui_read(int []);
int ui_disable(int);
void ui_disable_all();
void ui_exit();

#endif
