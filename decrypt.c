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

   return 0;

   /* create buffers */
   gerr = gpgme_data_new(&data);
   if(gerr != GPG_ERR_NO_ERROR) return 12;

   gerr = gpgme_data_new(&g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) return 20;

   gerr = gpgme_data_new(&g_encrypt);
   if(gerr != GPG_ERR_NO_ERROR) return 14;

   gerr = gpgme_data_new(&g_encrypt_send);
   if(gerr != GPG_ERR_NO_ERROR) return 24;

   /* fill buffers */
   /* gerr = gpgme_data_new(&g_plain);
   if(gerr != GPG_ERR_NO_ERROR) return 13;

   printf("strlen(%s) = %d\n",msg,i);
   i -= gpgme_data_write(g_plain, msg, i);
   if(i) {
      printf("size mismatch\n");
      return 12;
   } */
   strncpy(msg, "==> Erste Nachricht\n\n", EOF_L_MESSAGE);
   i = strlen(msg);
   gerr = gpgme_data_new_from_mem (&g_plain, msg, i, 0);


   /* setup recipient */
   gerr = gpgme_op_keylist_start(g_context, "nico schottelius", 0);
   if(gerr != GPG_ERR_NO_ERROR) return 11;

   i=0;
   gerr = gpgme_op_keylist_next(g_context, &g_recipient[0]);
   while((gpg_err = gpg_err_code(gerr)) != GPG_ERR_EOF) {
      /* for testing: one call of gpgme_op_keylist_next is enough */
      break;
      if(gerr == GPG_ERR_INV_VALUE) {
         printf("invalid pointer\n");
         return 15;
      } else if(gerr == GPG_ERR_ENOMEM) {
         printf("no mem\n");
         return 16;
      }

      printf ("%s: %s <%s> (%d)\n", g_recipient[0]->subkeys->keyid, g_recipient[0]->uids->name, g_recipient[0]->uids->email, i);
      i++;

      /* FIXME: this resets the good filled buffer ... */
      gerr = gpgme_op_keylist_next(g_context, &g_recipient[0]);
   }
   g_recipient[1] = NULL;

   /* all above seems to be wrong ... */
   gerr = gpgme_get_key(g_context,"775506B45998BF57D0D4AFF27C6E747C38616ADC", &g_recipient[0], 0);
   if(gerr != GPG_ERR_NO_ERROR) return 32;


   /* en/decrypt message */
   //gerr = gpgme_op_encrypt_sign(g_context, g_recipient, 0, g_plain, g_encrypt);
   gerr = gpgme_op_encrypt(g_context, g_recipient, 0, g_plain, g_encrypt);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("gerr=%d\n",gerr);
      return 18;
   }

   /* transfer the data into our own buffer,
    * so the data is saved; you cannot
    * reuse the gpgme buffers directly as in
    *    gerr = gpgme_op_decrypt(g_context, g_encrypt, g_plain_recv);
    *
    */
   i = gpgme_data_seek(g_encrypt, 0, SEEK_END);

   if(i > BIGBUF) return 22;
   printf("buflen: %d\n",i);
   
   /* reset to the beginning */
   gpgme_data_seek(g_encrypt, 0, SEEK_SET);

   if(gpgme_data_read(g_encrypt, b_encrypt, i) == -1) {
      perror("pgme_data_read");
      return 23;
   }
   printf("crypt:\n%s\n", b_encrypt);
   /* until here it works, testcrypt contains
    * data and can be decrypted ...
    *
    * perhaps the context needs some reset?
    */

   if((tmp = gpgme_data_write(g_encrypt_send, b_encrypt, i)) == -1) {
      perror("pgme_data_write");
      return 23;
   }
   printf("crypt-wrote:%d\n", tmp);

   /* look for contexts */

   gerr = gpgme_op_decrypt(g_context, g_encrypt_send, g_plain_recv);
   if(gerr != GPG_ERR_NO_ERROR) {
      printf("gerr=%d\n",gerr);
      return 19;
   }

   /* open communication channel: netcat */

   /* listen for input from:
    * stdin
    * communication channel
    */

   /* de/encode data from comm channel */

   return 1;
}
