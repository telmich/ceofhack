#include <gpgme.h>
#include <string.h>     /* strncpy */
#include <fcntl.h>
#include <unistd.h>

char *home="/home/nico/.ceof/gpg";

#include "ceofhack.h"

int main()
{
   int fd;

   gpgme_ctx_t g_context;
   gpgme_data_t data;

   gpgme_error_t gerr;
   gpg_err_code_t gpg_err;

   gpgme_data_t g_plain;
   gpgme_data_t g_plain_recv;
   gpgme_data_t g_encrypt;
   gpgme_data_t g_encrypt_send;

   gpgme_key_t g_recipient[MAX_RCP+1];
   char *p;
   char b_encrypt[BIGBUF+1];

   char msg[EOF_L_MESSAGE];
   char msg_in[EOF_L_MESSAGE];

   int i, tmp;

   for(i=0;i<EOF_L_MESSAGE; i++) msg_in[i] = 0;
   for(i=0;i<EOF_L_MESSAGE; i++) msg[i] = 0;
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
   gpgme_set_armor(g_context, 1);

   /* read crypted data */
   fd = open("testcrypt",O_RDONLY);
   if(fd == -1) return 40;
   if((tmp = read(fd, b_encrypt, BIGBUF)) == -1) return 41;
   close(fd);
   printf("crypt-in: %s\n", b_encrypt);


   /* create buffers */
   gerr = gpgme_data_new(&g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) return 20;

   gerr = gpgme_data_new(&g_encrypt_send);
   if(gerr != GPG_ERR_NO_ERROR) return 24;
   
   /* set encoding */
   gerr = gpgme_data_set_encoding(g_plain_recv, GPGME_DATA_ENCODING_ARMOR);
   if(gerr != GPG_ERR_NO_ERROR) return 25;

   i = strlen(b_encrypt);  
   printf("strlen(%s) = %d\n",b_encrypt,i);
   i -= gpgme_data_write(g_encrypt_send, b_encrypt, i);
   if(i) {
      printf("size mismatch\n");
      return 12;
   }

   /* decrypt */
   gerr = gpgme_op_decrypt(g_context, g_encrypt_send, g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("gerr=%d\n",gerr);
      return 19;
   }

   return 1;
}
