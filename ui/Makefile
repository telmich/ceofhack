include ../Makefile.include

CC+=-I..

################################################################################
# User interface

UI_MAIN=ui_cmd_main.c
LIB=../lib/eof_ui_connect.c ../lib/eof_get_ui_socketpath.c ../lib/eof_get_configdir.c
LIB+=../lib/eof_ui_register.c ../lib/eof_ui_deregister.c ../lib/eof_va_write.c
LIB+=../lib/eof_ui_peer_add.c ../lib/eof_ui_peer_list.c ../lib/eof_ui_peer_send.c
LIB+=../lib/eof_ui_peer_rename.c ../lib/eof_ui_peer_show.c
SHCL=../read_all.c ../write_all.c 
UI=$(UI_MAIN) $(LIB) $(SHCL)
UI_OBJ=$(UI:.c=.o)
UI_PROG=$(UI:.c=)

all: ui_cmd

run: ui_cmd
	./$^

clean:
	rm -f $(UI_OBJ) ui_cmd

$(UI_OBJ): ../eof.h
################################################################################
# Individual make rules

ui_cmd: $(UI_OBJ)
	$(CC) -o $@ $^
