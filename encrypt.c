#include <gpgme.h>
#include <string.h>     /* strncpy */
#include <fcntl.h>
#include <unistd.h>

char *home="/home/user/nico/.ceof/gpg";

#include "ceofhack.h"

gpgme_error_t getpwd(void *HOOK, const char *UID_HINT,
                     const char *PASSPHRASE_INFO,
                     int PREV_WAS_BAD, int FD) {

   printf("getpwd called, %d, %s\n", PREV_WAS_BAD, PASSPHRASE_INFO);

   write_all(FD, "123456\n", 7);

   return 0;
}

int main()
{
   gpgme_ctx_t g_context;
   gpgme_error_t gerr;
   gpgme_data_t g_plain_input;
   gpgme_data_t g_encrypt_output;
   gpgme_key_t  g_key[2];


   char *p;
   char b_encrypt[BIGBUF+1];
   char b_output[BIGBUF+1];
   int i, tmp;
   int fd;

   for(i=0;i<=BIGBUF; i++) {
      b_encrypt[i] = 0;
      b_output[i] = 0;
   }

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
   fd = open("plaintext",O_RDONLY);
   if(fd == -1) return 40;
   if((tmp = read(fd, b_encrypt, BIGBUF)) == -1) return 41;
   close(fd);
   printf("readfromfile: %d\n", tmp);

   i = strlen(b_encrypt);  
   printf("strlen(%s) = %d\n",b_encrypt,i);

   gerr = gpgme_data_new(&g_encrypt_output);
   if(gerr != GPG_ERR_NO_ERROR) return 24;

   /* THIS WORKS */
   gerr = gpgme_data_new_from_mem(&g_plain_input, b_encrypt, i, 1);
   if(gerr != GPG_ERR_NO_ERROR) return 24;
   
   /* retrieve keyid */
   gerr = gpgme_op_keylist_start(g_context, "Nico Schottelius", 0);
   if(gerr != GPG_ERR_NO_ERROR) return 50;
   gerr = gpgme_op_keylist_next(g_context, &g_key[0]);
   if(gerr != GPG_ERR_NO_ERROR) return 51;
   if(gerr == GPG_ERR_EOF) printf("alle schlüssel gefunden\n");
   g_key[1] = NULL;

   /* encrypt: from gpgme_data_new_from_mem()  */
   gerr = gpgme_op_encrypt(g_context, g_key, GPGME_ENCRYPT_ALWAYS_TRUST,
                           g_plain_input, g_encrypt_output);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("gerr=%d\n",gerr);
      return 19;
   }

   gerr = gpgme_data_seek(g_encrypt_output, 0, SEEK_SET);
   if(gerr != GPG_ERR_NO_ERROR) return 53;

   tmp = gpgme_data_read(g_encrypt_output, b_output, BIGBUF);  
   printf("geschrieben: %d\n", tmp);

   fd = open("text.encrypted",O_WRONLY | O_CREAT);
   if(fd == -1) return 57;
   if((tmp = write_all(fd, b_output, tmp)) == -1) return 41;
   close(fd);
   printf("geschrieben (datei): %d\n", tmp);

   return 1;
}
