#ifndef THIS_IS_AN_UGLY_CEOF_HACK
#define THIS_IS_AN_UGLY_CEOF_HACK

/* the library version is not yet used */

#define LIBEOF_VERSION "E.O.F"

/* those values are from the current EOF specs */

#define EOF_L_NICKNAME 128
#define EOF_L_MESSAGE  128
#define EOF_L_ADDRESS  128

#define SIZE 1024
#define MAX_RCP 1
#define BIGBUF 65536

/* need to listen on stdin and ipv4 socket */
#define HP_LAST 2

/* Structures */
struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
};

struct peers {
   struct peer peer;
   struct peers *next;
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


#endif
