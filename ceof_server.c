#include <gpgme.h>

char *home="/home/user/nico/.ceof/gnupg";
#define SIZE 1024


int main()
{
   gpgme_error_t gerr;
   gpgme_ctx_t ceofcontext;
   gpgme_engine_info_t enginfo;
   gpgme_data_t data;

   gpgme_data_t g_plain;
   gpgme_data_t g_encrypt;
   char *p;

   p = gpgme_check_version(NULL);

   gerr = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(gerr != GPG_ERR_NO_ERROR) return 10;

   p = gpgme_get_protocol_name(GPGME_PROTOCOL_OpenPGP);
   printf("Version: %s\n",p);


   gerr = gpgme_set_engine_info(GPGME_PROTOCOL_OpenPGP, NULL, home);

   if(gerr == GPG_ERR_NO_ERROR) {
      printf("gpgme_set_engine_info: ok\n");
   } else {
      printf("gpgme_set_engine_info: err\n");
   }

   /* get engine information */
   gerr = gpgme_get_engine_info(&enginfo);
   if(gerr != GPG_ERR_NO_ERROR) return 3;

   printf("file=%s, home=%s\n",enginfo->file_name,enginfo->home_dir);

   /* create our own context */
   gerr = gpgme_new(&ceofcontext);
   if(gerr != GPG_ERR_NO_ERROR) return 1;


   /* FIXME: both needed? */
   /* FIXME: why is the path (FILE_NAME) needed? */
   /* FIXME: /usr/bin/gpg must be changed to ~/.ceof/gpg/binary or similar */
   gerr = gpgme_ctx_set_engine_info (ceofcontext, GPGME_PROTOCOL_OpenPGP,
               "/usr/bin/gpg","/home/user/nico/.ceof/gpg/");
   if(gerr != GPG_ERR_NO_ERROR) return 4;

   /* do not ascii armor data; use 1 for testing */
   //gpgme_set_armor(ceofcontext, 0);
   gpgme_set_armor(ceofcontext, 1);

   /* create buffer */
   gerr = gpgme_data_new(&data);
   if(gerr != GPG_ERR_NO_ERROR) return 6;


   /* open communication channel: netcat */

//   forkexecpipe

   /* listen for input from:
    * stdin
    * communication channel
    */

   /* de/encode data from comm channel */

   return 1;
}
