include ../Makefile.include

CC+=-I..

################################################################################
# User interface

UI_MAIN=ui_cmd_main.c
LIB=../lib/eof_ui_connect.c ../lib/eof_get_ui_socketpath.c ../lib/eof_get_configdir.c
LIB+=../lib/eof_ui_register.c ../lib/eof_ui_deregister.c ../lib/eof_va_write.c
LIB+=../lib/eof_ui_peer_add.c ../lib/eof_ui_peer_list.c ../lib/eof_ui_peer_send.c
LIB+=../lib/eof_ui_peer_rename.c ../lib/eof_ui_peer_show.c ../lib/eof_ui_quit.c
LIB+=../lib/eof_va_read.c ../lib/eof_id_init.c ../lib/eof_id_new.c
LIB+=../lib/eof_ui_init.c
SHCL=../read_all.c ../write_all.c 
UI=$(UI_MAIN) $(LIB) $(SHCL)
UI_OBJ=$(UI:.c=.o)
UI_PROG=$(UI:.c=)

UI_LO=ui_cmd_listen.c $(LIB) $(SHCL)
UI_LO_OBJ=$(UI_LO:.c=.o)

UI_PEER_SEND=ui_cmd_peer_send.c $(LIB) $(SHCL)
UI_PEER_SEND_OBJ=$(UI_PEER_SEND:.c=.o)

UI_PEER_ADD=ui_cmd_peer_add.c $(LIB) $(SHCL)
UI_PEER_ADD_OBJ=$(UI_PEER_ADD:.c=.o)

UI_PEER_RENAME=ui_cmd_peer_rename.c $(LIB) $(SHCL)
UI_PEER_RENAME_OBJ=$(UI_PEER_RENAME:.c=.o)

UI_PEER_LIST=ui_cmd_peer_list.c $(LIB) $(SHCL)
UI_PEER_LIST_OBJ=$(UI_PEER_LIST:.c=.o)

UI_QUIT=ui_cmd_quit.c $(LIB) $(SHCL)
UI_QUIT_OBJ=$(UI_QUIT:.c=.o)

PROG=ui_cmd ui_cmd_listen ui_cmd_peer_send ui_cmd_quit ui_cmd_peer_add ui_cmd_peer_list
PROG+=ui_cmd_peer_rename

all: $(PROG)

run: ui_cmd
	./$^

clean:
	rm -f $(UI_OBJ) $(PROG)

$(UI_OBJ): ../eof.h
################################################################################
# Individual make rules

ui_cmd: $(UI_OBJ)
	$(CC) -o $@ $^

ui_cmd_listen: $(UI_LO_OBJ)
	$(CC) -o $@ $^

ui_cmd_peer_add: $(UI_PEER_ADD_OBJ)
	$(CC) -o $@ $^

ui_cmd_peer_rename: $(UI_PEER_RENAME_OBJ)
	$(CC) -o $@ $^

ui_cmd_peer_list: $(UI_PEER_LIST_OBJ)
	$(CC) -o $@ $^

ui_cmd_peer_send: $(UI_PEER_SEND_OBJ)
	$(CC) -o $@ $^

ui_cmd_quit: $(UI_QUIT)
	$(CC) -o $@ $^
