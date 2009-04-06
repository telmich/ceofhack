LDFLAGS= $(shell gpgme-config --libs)

CC=gcc -std=c99 -Wall -Wextra -Werror -pedantic -pipe -g -D_FILE_OFFSET_BITS=64 -lgpgme -I.
CC=gcc -std=c99 -Wall -Wextra -Werror -pipe -g -D_FILE_OFFSET_BITS=64 -lgpgme -I.
CC=gcc -Wall -Wextra -Werror -pipe -g -D_FILE_OFFSET_BITS=64 -lgpgme -I.
# above are too strict right now :-/
#CC=gcc -Wall -Werror -pipe -g -D_FILE_OFFSET_BITS=64 -lgpgme -I.

CCONFIG=cconfig_tree.c cconfig_find_fn.c cconfig_tree_dump.c cconfig_entries_get.c
CCONFIG+=cconfig_entry_fn.c

# Small helper c library
SHCL=openreadclosestatic.c

TRANSPORT_PROTO=tp_init.c tp_add_available.c tp_listen_add.c tp_listen_init.c
TRANSPORT_PROTO+=tp_scheme_len.c tp_available.c
TRANSPORT_PROTO+=tp_listen_read.c tp_send.c tp_send_wait.c

PEER=peers_init.c peer_add.c peer_list.c peer_findbyname.c peer_send.c
PEER+=peer_keyid_get.c peer_addr_get.c peer_input.c

HELPER=helper_fdonly.c helper_new.c helper_exec.c
HELPER+=helper_write.c
#HELPER+=helper_write.c helper_read.c

CEOFHACK=main.c forkexecpipe.c fd_to_poll.c signals_init.c signal_child.c
CEOFHACK+=cmds_init.c cmd_add.c cmd_check.c
CEOFHACK+=user_input.c ui_quit.c ui_help.c check_input.c
CEOFHACK+=cgpg_init.c cgpg_keyid_get.c cgpg_encrypt.c
CEOFHACK+=config_init.c
CEOFHACK+=$(CCONFIG) $(TRANSPORT_PROTO) $(SHCL) $(PEER) $(HELPER)
CEOFHACK_O=$(CEOFHACK:.c=.o)

PROG=ceofhack decrypt

DOC=doc/EOF

all: $(PROG) tp-all

run: $(PROG)
	cat doc/dev/braindumps/sample-commands
	./$(PROG)

clean: tp-clean
	rm -f $(CEOFHACK_O) $(PROG) *.o

test: tests/testcconfig ceofhack
	./tests/testcconfig .
	./ceofhack; echo $$?
	killall netcat

tests/testcconfig: tests/testcconfig.c cconfig_tree.c
	$(CC) -o $@ $^

ceofhack: $(CEOFHACK_O)
	$(CC) -o $@ $^

ceof_server_exec: ceof_server
	./ceof_server

ceof_server: ceof_server.c
	$(CC) -o $@ $^

gpgmedecrypt: fromgpgmestolen/t-decrypt.c
	$(CC) -o $@ $^

decrypt: decrypt.c
	$(CC) -o $@ $^

decrypt-test:
	gpg --homedir ~/.ceof/gpg/ --decrypt < ./testcrypt

$(CEOFHACK_O): ceofhack.h eof.h Makefile

documentation: doc/EOF.tex
	make -C doc all

viewdoc: documentation
	evince doc/EOF.pdf

tp-all:
	make -C tp all

tp-clean:
	make -C tp clean
