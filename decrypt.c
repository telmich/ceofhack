#include <gpgme.h>
#include <string.h>     /* strncpy */
#include <fcntl.h>
#include <unistd.h>

char *home="/home/nico/.ceof/gpg";

#include "ceofhack.h"

gpgme_error_t getpwd(void *HOOK, const char *UID_HINT,
                     const char *PASSPHRASE_INFO,
                     int PREV_WAS_BAD, int FD) {

   printf("getpwd called, %d, %s\n", PREV_WAS_BAD, PASSPHRASE_INFO);

   write(FD, "123456\n", 7);

   return 0;
}

int main()
{
   gpgme_ctx_t g_context;
   gpgme_error_t gerr;
   gpgme_data_t g_plain_recv;
   gpgme_data_t g_encrypt_send;

   char *p;
   char b_encrypt[BIGBUF+1];

   int i, tmp;
   int fd;

   for(i=0;i<=BIGBUF; i++) b_encrypt[i] = 0;

   /* init the gpgme library */
   gpgme_check_version(NULL);

   /* which must support OpenPGP */
   gerr = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(gerr != GPG_ERR_NO_ERROR) return 4;

   /* DEBUG: retrieve protocol name */
   p = (char *) gpgme_get_protocol_name(GPGME_PROTOCOL_OpenPGP);
   printf("Version: %s\n",p);

   /* create our own context */
   gerr = gpgme_new(&g_context);
   if(gerr != GPG_ERR_NO_ERROR) return 1;
   gerr = gpgme_ctx_set_engine_info (g_context, GPGME_PROTOCOL_OpenPGP,
               "/usr/bin/gpg",home);
   if(gerr != GPG_ERR_NO_ERROR) return 2;

   /* do not ascii armor data; use 1 for testing only */

   /* FIXME: test: it is not in t-decrypt.c */
   gpgme_set_armor(g_context, 1);

   gpgme_set_passphrase_cb(g_context, getpwd, NULL);

   /* FIXME: test: it is not in t-decrypt.c */
   /* read crypted data */
   fd = open("testcrypt",O_RDONLY);
   if(fd == -1) return 40;
   if((tmp = read(fd, b_encrypt, BIGBUF)) == -1) return 41;
   close(fd);

   /* create buffers */
   gerr = gpgme_data_new(&g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) return 20;

   /* FIXME: test: it is not in t-decrypt.c */
   gerr = gpgme_data_new(&g_encrypt_send);
//   gerr = gpgme_data_new_from_file (&g_encrypt_send, "./testcrypt", 1);
   if(gerr != GPG_ERR_NO_ERROR) return 24;
   
   i = strlen(b_encrypt);  
   printf("strlen(%s) = %d\n",b_encrypt,i);
   gpgme_data_write(g_encrypt_send, b_encrypt, i);

   /* decrypt */
   gerr = gpgme_op_decrypt(g_context, g_encrypt_send, g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("gerr=%d\n",gerr);
      return 19;
   }

   return 1;
}
