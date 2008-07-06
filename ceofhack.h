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

struct peer {
   char name[EOF_L_NICKNAME+1];
   char addr[EOF_L_ADDRESS+1];
};

#endif
