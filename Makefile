LDFLAGS= $(shell gpgme-config --libs)

CC=gcc -g -D_FILE_OFFSET_BITS=64 -lgpgme -Wall 

CEOFHACK=main.c forkexecpipe.c fd_to_poll.c signals_init.c signal_child.c
CEOFHACK+=helper_fdonly.c helper_new.c helper_exec.c
CEOFHACK+=cmds_init.c cmd_add.c cmd_check.c
CEOFHACK+=user_input.c ui_quit.c
CEOFHACK+=check_input.c
CEOFHACK+=peers_init.c peer_add.c
CEOFHACK_O=$(CEOFHACK:.c=.o)
PROG=ceofhack decrypt

all: $(PROG)

clean:
	rm -f $(CEOFHACK_O) $(PROG)

test: ceofhack
	./ceofhack; echo $$?

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

$(CEOFHACK_O): ceofhack.h
