#include <gpgme.h>
#include <string.h>     /* strncpy */

char *home="/home/user/nico/.ceof/gnupg";
#define SIZE 1024

#define MAX_RCP 1
#define EOF_MSG_SIZE 64

int main()
{
   gpgme_ctx_t g_context;
   gpgme_engine_info_t enginfo;
   gpgme_data_t data;

   gpgme_error_t gerr;
   gpg_err_code_t gpg_err;

   gpgme_data_t g_plain;
   gpgme_data_t g_encrypt;

   gpgme_key_t g_recipient[MAX_RCP+1];
   char *p;

   char msg[EOF_MSG_SIZE];
   char msg_in[EOF_MSG_SIZE];

   int i;

   strncpy(msg,"Erste Nachricht",EOF_MSG_SIZE);
   for(i=0;i<EOF_MSG_SIZE; i++) msg_in[i] = 0;

   gpgme_check_version(NULL);

   gerr = gpgme_engine_check_version(GPGME_PROTOCOL_OpenPGP);
   if(gerr != GPG_ERR_NO_ERROR) return 10;

   p = (char *) gpgme_get_protocol_name(GPGME_PROTOCOL_OpenPGP);
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
   gerr = gpgme_new(&g_context);
   if(gerr != GPG_ERR_NO_ERROR) return 1;


   /* FIXME: both needed? */
   /* FIXME: why is the path (FILE_NAME) needed? */
   /* FIXME: /usr/bin/gpg must be changed to ~/.ceof/gpg/binary or similar */
   gerr = gpgme_ctx_set_engine_info (g_context, GPGME_PROTOCOL_OpenPGP,
               "/usr/bin/gpg","/home/user/nico/.ceof/gpg/");
   if(gerr != GPG_ERR_NO_ERROR) return 4;

   /* do not ascii armor data; use 1 for testing */
   //gpgme_set_armor(g_context, 0);
   gpgme_set_armor(g_context, 1);

   /* create buffers */
   gerr = gpgme_data_new(&data);
   if(gerr != GPG_ERR_NO_ERROR) return 12;

   gerr = gpgme_data_new(&g_plain);
   if(gerr != GPG_ERR_NO_ERROR) return 13;

   gerr = gpgme_data_new(&g_encrypt);
   if(gerr != GPG_ERR_NO_ERROR) return 14;

   /* fill buffers */
   i = strlen(msg);
   i -= gpgme_data_write(g_plain, msg, i);
   if(i) {
      printf("size mismatch\n");
      return 12;
   }

   /* setup recipient */
   gerr = gpgme_op_keylist_start(g_context, "nico schottelius", 0);
   if(gerr != GPG_ERR_NO_ERROR) return 11;

   i=0;
   gerr = gpgme_op_keylist_next(g_context, &g_recipient[0]);
   while((gpg_err = gpg_err_code(gerr)) != GPG_ERR_EOF) {
      if(gerr == GPG_ERR_INV_VALUE) {
         printf("invalid pointer\n");
         return 15;
      } else if(gerr == GPG_ERR_ENOMEM) {
         printf("no mem\n");
         return 16;
      }

      printf ("%s: %s <%s> (%d)\n", g_recipient[0]->subkeys->keyid, g_recipient[0]->uids->name, g_recipient[0]->uids->email, i);
      i++;
      gerr = gpgme_op_keylist_next(g_context, &g_recipient[0]);
   }
   g_recipient[1] = NULL;


   /* en/decrypt message */
   gerr = gpgme_op_encrypt(g_context, g_recipient, 0, g_plain, g_encrypt);
   if(gerr != GPG_ERR_NO_ERROR) return 18;

   gerr = gpgme_op_decrypt(g_context, g_encrypt, g_plain);
   if(gerr != GPG_ERR_NO_ERROR) return 17;



   /* open communication channel: netcat */

//   forkexecpipe

   /* listen for input from:
    * stdin
    * communication channel
    */

   /* de/encode data from comm channel */

   return 1;
}
