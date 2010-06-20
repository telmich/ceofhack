# 
# 2008-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
# 
# This file is part of ceofhack.
#
# ceofhack is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ceofhack is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ceofhack. If not, see <http://www.gnu.org/licenses/>.
#

include Makefile.include

# cconfig modules
CCONFIG=cconfig_tree.c cconfig_find_fn.c cconfig_tree_dump.c cconfig_entries_get.c
CCONFIG+=cconfig_entry_fn.c

# Small helper c library
SHCL=openreadclosestatic.c convert.c forkexecpipe.c
SHCL+=fileexists.c openwriteclose.c close_all.c close_on_exec.c
SHCL+=shcl/shcl_read_all.c shcl/shcl_write_all.c

TRANSPORT_PROTO=tp_init.c tp_add_available.c tp_listen_add.c tp_listen_init.c
TRANSPORT_PROTO+=tp_scheme_len.c tp_available.c
TRANSPORT_PROTO+=tp_listen_read.c tp_send.c tp_send_wait.c tp_getscheme.c

PEER=peer_init.c peer_add.c peer_findbyname.c peer_send.c
PEER+=peer_keyid_get.c peer_addr_get.c
PEER+=peer_new.c peer_list.c peer_rename.c peer_show.c

# help to execute external stuff
HELPER=helper_init.c helper_fdonly.c helper_new.c helper_exec.c
HELPER+=helper_write.c helper_find_by_pid.c helper_disable.c helper_find_by_fd.c
HELPER+=helper_signal_all.c helper_check_input.c helper_signal.c
HELPER+=helper_find_by_handle.c

ONION=onion_partial_create_msg_drop.c onion_partial_create.c

# command handling (ceof internal)
CMD=cmd_init.c
CMD+=cmd_20xx.c cmd_2000.c cmd_2002.c cmd_2003.c
CMD+=cmd_1103.c
CMD+=cmd_21xx.c cmd_2100.c cmd_2101.c cmd_2102.c cmd_2103.c cmd_2104.c
CMD+=cmd_2105.c cmd_2106.c cmd_2199.c
CMD+=cmd_3000.c

# EOF subsystems
#EOFS=eofs_init.c eofs_iterate.c
EOFS=

# ceof (the next generation EOFi ;-))
CEOF=ceof_exit.c ceof_banner.c ceof_runs.c

# objects from the upcoming library for EOFi (=ceofhack)
LIB=lib/eof_get_configdir.c lib/eof_get_crypto_dir.c lib/eof_get_tp_dir.c
LIB+=lib/eof_get_ui_socketpath.c lib/eof_get_pidfile.c lib/eof_get_mykeyid_file.c
LIB+=lib/eof_va_read.c lib/eof_va_write.c
LIB+=lib/eof_id_init.c lib/eof_id_new.c lib/eof_cmd_handle.c lib/eof_cmd_cat_get_default_cmd.c
LIB+=lib/eof_cmd_init.c lib/eof_cmd_cat_init.c lib/eof_cmd_create.c lib/eof_cmd_find_in_cat.c 
LIB+=lib/eof_cmd_cat_add.c

# interface for the user interfaces
UI=ui_init.c ui_handle.c ui_read.c ui_disable.c ui_disable_all.c ui_exit.c

# Crypto parts within ceofhack
CRYPTO=crypto_init.c

# Crypto part within ceof-crypto (standalone)
CEOF_CRYPTO_CMD=crypto/crypto_cmd_default.c crypto/cmd_1200.c
CEOF_CRYPTO=crypto/crypto_main.c crypto/crypto_gpg_init.c
CEOF_CRYPTO+=crypto/crypto_gpg_encrypt.c
CEOF_CRYPTO+=crypto/crypto_gpg_keyid_get.c crypto/crypto_gpg_decrypt.c
CEOF_CRYPTO+=crypto/crypto_usage.c crypto/crypto_cmd_init.c
CEOF_CRYPTO+=$(LIB) $(CEOF_CRYPTO_CMD) shcl/shcl_read_all.c shcl/shcl_write_all.c


# ceofhack internal
CEOFHACK=main.c fd_to_poll.c signals_init.c signal_child.c
CEOFHACK+=config_init.c $(ONION)
CEOFHACK+=$(CCONFIG) $(TRANSPORT_PROTO) $(SHCL) $(PEER) $(HELPER)
CEOFHACK+=$(UI_CMD) $(CMD) $(CEOF) $(CRYPTO) $(UI) $(LIB) $(EOFS)

# objects
CEOFHACK_O=$(CEOFHACK:.c=.o)
CEOF_CRYPTO_O=$(CEOF_CRYPTO:.c=.o)

# headers
HEADERS_GENERIC=eof.h
HEADERS_CEOF=ceof.h version.h

HEADERS_CEOFHACK=ceofhack.h $(HEADERS_GENERIC) $(HEADERS_CEOF)
HEADERS_CEOF_CRYPTO=crypto.h  $(HEADERS_GENERIC) $(HEADERS_CEOF)

PROG=ceofhack ceof-crypto

DOC=doc/EOF

all: $(PROG)
	for eofs in $(EOFs); do make -C $$eofs $@; done

clean:
	rm -f $(CEOFHACK_O) $(PROG) *.o
	for eofs in $(EOFs); do make -C $$eofs $@; done

run: $(PROG)
	cat doc/dev/braindumps/sample-commands
	./$(PROG)

version.h: .savedversion
.savedversion:
	./scripts/version

debug: $(PROG)
	gdb ./$(PROG)

# tests
tests: tests.o $(LIB:.c=.o) $(SHCL:.c=.o)
	$(CC) -lcheck -o $@ $^
	./tests

tests/testcconfig: tests/testcconfig.c cconfig_tree.c
	$(CC) -o $@ $^


$(CEOFHACK_O): $(HEADERS_CEOFHACK) Makefile Makefile.include
ceofhack: $(CEOFHACK_O)
	$(LD) -o $@ $^

$(CEOF_CRYPTO_O): $(HEADERS_CEOF_CRYPTO) Makefile Makefile.include
ceof-crypto: $(CEOF_CRYPTO_O)
	$(LD) -o $@ $^

# Install
install: ceofhack
	install ceofhack $(DESTDIR)/usr/bin

documentation: doc/EOF.tex
	make -C doc all

viewdoc: documentation
	evince doc/EOF.pdf

pub:
	git push --mirror
	git push --mirror github
	git push --mirror gitorious

release: pub
	./scripts/release
