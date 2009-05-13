include ../Makefile.include

CC+=-I..

################################################################################
# User interface

UI_MAIN=ui_cmd_main.c
LIB=eof_ui_connect.c eof_ui_get_socket_path.c
UI=$(UI_MAIN) $(LIB)
UI_OBJ=$(UI:.c=.o)
UI_PROG=$(UI:.c=)

all: ui_cmd

clean:
	rm -f $(UI_OBJ) ui_cmd

################################################################################
# Individual make rules

ui_cmd: $(UI_OBJ)
	$(CC) -o $@ $^
