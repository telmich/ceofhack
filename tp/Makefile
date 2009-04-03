CC=gcc -Wall -Wextra -Werror -pipe -g -D_FILE_OFFSET_BITS=64 -I..

DUMMY_C=dummy/c/listen.c dummy/c/send.c
TCP_C=tcp/c/listen.c

TPS=
TPS+=$(DUMMY_C)
TPS+=$(TCP_C)

TPS_OBJ=$(TPS:.c=.o)
TPS_PROG=$(TPS:.c=)

all: $(TPS_PROG)

clean:
	rm -f $(TPS_OBJ) $(TPS_PROG)
