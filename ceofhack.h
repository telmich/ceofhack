#ifndef THIS_IS_AN_UGLY_CEOF_HACK
#define THIS_IS_AN_UGLY_CEOF_HACK

#include <poll.h>    /* pollfd */

/* the library version is not yet used */

#define LIBEOF_VERSION "E.O.F"

/*
 * those values are from the current EOF specs
 */

/* gui2user */
#define EOF_L_GUI       256

/* basics */
#define EOF_L_NICKNAME  128
#define EOF_L_MESSAGE   128
#define EOF_L_ADDRESS   128

#define SIZE 1024
#define MAX_RCP 1
#define BIGBUF 65536

#define MAX_COMM 64 /* maximum number of communication channels
                          contains stdin, listen sockets
                          and outgoing sockets */

/* need to listen on stdin and ipv4 socket */
#define HP_LAST 2

/* commands */
#define UI_QUIT      "/quit"

/* user commands */

/* Structures */
struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
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
#include <sys/types.h>           /* FIXME: posix correct header?) */
struct helper {                  /* for the subprojects           */
   pid_t pid;                    /* process id                    */
   int fds[2];                   /* file deskriptors used by poll */
   char *path;                   /* path relative to config dir   */
   int (*handle)(int []);        /* pointer to the handler        */
   int (*exit)(int []);          /* pointer to the exit function  */
};

/* Global variables  */
extern struct helper chp[MAX_COMM];
extern struct pollfd pfd[MAX_COMM];
extern struct cmd    cmds;
extern int chp_cnt;


/* Functions */
int forkexecpipe(char *path, struct helper *hp);
void fd_to_poll();
int signals_init();
void signal_child(int sig);

int helper_new();
int helper_fdonly(int fd, int (*handle)(int []), int (*exit)(int []));

int cmds_init();
int cmd_add(char *name, int (*handle)(char *));
int ui_quit(char *args);


#endif
