include ../Makefile.include

CC+=-I..

################################################################################
# Available transport protocols

DUMMY_C=dummy/c/listen.c dummy/c/send.c
TCP_C=tcp/c/listen.c
TCP_C2=tcp/c2/listen.c tcp/c2/send.c
TCP_C3=tcp/c3/listen.c

################################################################################
# Enabled (for compiling) transport protocols
TPS=
TPS+=$(DUMMY_C)
TPS+=$(TCP_C)
#TPS+=$(TCP_C2)
TPS+=$(TCP_C3)

TPS_OBJ=$(TPS:.c=.o)
TPS_PROG=$(TPS:.c=)

all: $(TPS_PROG)

clean:
	rm -f $(TPS_OBJ) $(TPS_PROG)

################################################################################
# Individual make rules

tcp/c2/listen: tcp/c2/init_socket.o tcp/c2/do_socket.o tcp/c2/sigio.o tcp/c2/handle_conn.o
	$(CC) $^ -o $@
tcp/c3/listen: ../read_all.o $(TCP_C3)
	$(CC) $^ -o $@
