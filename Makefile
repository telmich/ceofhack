include Makefile.include

# cconfig modules
CCONFIG=cconfig_tree.c cconfig_find_fn.c cconfig_tree_dump.c cconfig_entries_get.c
CCONFIG+=cconfig_entry_fn.c

# Small helper c library
SHCL=openreadclosestatic.c convert.c read_all.c write_all.c forkexecpipe.c

TRANSPORT_PROTO=tp_init.c tp_add_available.c tp_listen_add.c tp_listen_init.c
TRANSPORT_PROTO+=tp_scheme_len.c tp_available.c
TRANSPORT_PROTO+=tp_listen_read.c tp_send.c tp_send_wait.c

PEER=peers_init.c peer_add.c peer_list.c peer_findbyname.c peer_send.c
PEER+=peer_keyid_get.c peer_addr_get.c peer_input.c

# help to execute external stuff
HELPER=helper_init.c helper_fdonly.c helper_new.c helper_exec.c
HELPER+=helper_write.c helper_find_by_pid.c helper_disable.c helper_find_by_fd.c
#HELPER+=helper_write.c helper_read.c

# command line user interface
UI_CMD=ui_cmds_init.c ui_cmd_add.c ui_cmd_check.c ui_cmd_read.c
UI_CMD+=ui_quit.c ui_help.c ui_cmd_argcnt.c ui_cmd_argncpy.c

# command handling (ceofhack internal)
CMD=cmd_handle.c check_input.c cmd_init.c cmd_cat_create.c
CMD+=cmd_create.c cmd_cat_add.c cmd_cat_find.c cmd_find_in_cat.c
CMD+=cmd_2000.c cmd_2002.c cmd_2003.c
CMD+=cmd_3000.c

# gpg crypto
GPG=cgpg_init.c cgpg_keyid_get.c cgpg_encrypt.c cgpg_decrypt.c

# ceof: the next generation EOFi ;-)
CEOF=ceof_exit.c ceof_banner.c

# ceofhack internal
CEOFHACK=main.c fd_to_poll.c signals_init.c signal_child.c
CEOFHACK+=config_init.c
CEOFHACK+=$(CCONFIG) $(TRANSPORT_PROTO) $(SHCL) $(PEER) $(HELPER)
CEOFHACK+=$(UI_CMD) $(CMD) $(CEOF) $(GPG)
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

decrypt: decrypt.c $(SHCL)
	$(CC) -o $@ $^

decrypt-test:
	gpg --homedir ~/.ceof/gpg/ --decrypt < ./testcrypt

$(CEOFHACK_O): ceofhack.h ceof.h eof.h Makefile Makefile.include

documentation: doc/EOF.tex
	make -C doc all

viewdoc: documentation
	evince doc/EOF.pdf

tp-all:
	make -C tp all

tp-clean:
	make -C tp clean
