CC=gcc -Wall -Wextra -Werror -pipe -g -D_FILE_OFFSET_BITS=64 -I..

DUMMY_C=dummy/c/listen.c dummy/c/send.c
TCP_C=tcp/c/listen.c
TCP_C2=tcp/c2/listen.c tcp/c2/send.c

TPS=
TPS+=$(DUMMY_C)
TPS+=$(TCP_C)
TPS+=$(TCP_C2)

TPS_OBJ=$(TPS:.c=.o)
TPS_PROG=$(TPS:.c=)

all: $(TPS_PROG)

clean:
	rm -f $(TPS_OBJ) $(TPS_PROG)

################################################################################
# Individual make rules

tcp/c2/listen: tcp/c2/init_socket.o tcp/c2/do_socket.o
	$(CC) $^ -o $@
