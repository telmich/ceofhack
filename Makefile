LDFLAGS= $(shell gpgme-config --libs)

all: ceof_server
	./$^
ceof_server: ceof_server.c
	gcc -g -D_FILE_OFFSET_BITS=64 -lgpgme -Wall -o $@ $^


