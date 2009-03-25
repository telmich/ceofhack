LDFLAGS= $(shell gpgme-config --libs)

CC=gcc -g -D_FILE_OFFSET_BITS=64 -lgpgme -Wall -Werror -I.

CCONFIG=cconfig_tree.c cconfig_find_fn.c cconfig_tree_dump.c cconfig_entries_get.c
CCONFIG+=cconfig_entry_fn.c

# Small helper c library
SHCL=openreadclosestatic.c

TRANSPORT_PROTO=tp_init.c tp_add_available.c tp_add_enabled.c

CEOFHACK=main.c forkexecpipe.c fd_to_poll.c signals_init.c signal_child.c
CEOFHACK+=helper_fdonly.c helper_new.c helper_exec.c
CEOFHACK+=cmds_init.c cmd_add.c cmd_check.c
CEOFHACK+=user_input.c ui_quit.c ui_help.c
CEOFHACK+=check_input.c
CEOFHACK+=peers_init.c peer_add.c peer_list.c peer_findbyname.c peer_send.c
CEOFHACK+=peer_keyid_get.c
CEOFHACK+=cgpg_init.c cgpg_keyid_get.c cgpg_encrypt.c
CEOFHACK+=config_init.c
CEOFHACK+=peer_input.c
CEOFHACK+=$(CCONFIG) $(TRANSPORT_PROTO) $(SHCL)
CEOFHACK_O=$(CEOFHACK:.c=.o)
PROG=ceofhack decrypt

all: $(PROG)
	cat INPUT 
	./$(PROG)

clean:
	rm -f $(CEOFHACK_O) $(PROG)

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

$(CEOFHACK_O): ceofhack.h Makefile

documentation: doc/EOF.tex
	( cd doc && pdflatex EOF.tex && pdflatex EOF.tex && pdflatex EOF.tex )

viewdoc: documentation
	evince doc/EOF.pdf
