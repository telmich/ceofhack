include ../Makefile.include

CC+=-I..

################################################################################
# User interface

UI_MAIN=ui_cmd_main.c
LIB=../lib/eof_ui_connect.c ../lib/eof_get_ui_socketpath.c ../lib/eof_get_configdir.c
UI=$(UI_MAIN) $(LIB)
UI_OBJ=$(UI:.c=.o)
UI_PROG=$(UI:.c=)

all: ui_cmd

clean:
	rm -f $(UI_OBJ) ui_cmd

$(UI_OBJ): ../eof.h
################################################################################
# Individual make rules

ui_cmd: $(UI_OBJ)
	$(CC) -o $@ $^
