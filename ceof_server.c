#include <gpgme.h>

char *home="/home/user/nico/.ceof/gnupg";
#define SIZE 1024


int main()
{
   gpgme_error_t gerr;
   gerr = gpgme_set_engine_info(GPGME_PROTOCOL_OpenPGP, NULL, home);

   if(gerr == GPG_ERR_NO_ERROR) {
      printf("gpgme_set_engine_info: ok\n");
   } else {
      printf("gpgme_set_engine_info: err\n");
   }


   /* open communication channel: netcat */

//   forkexecpipe

   /* listen for input from:
    * stdin
    * communication channel
    */

   /* de/encode data from comm channel */

   return 1;
}
