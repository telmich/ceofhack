LDFLAGS= $(shell gpgme-config --libs)

CC=gcc -g -D_FILE_OFFSET_BITS=64 -lgpgme -Wall 

all: decrypt
ceof_server_exec: ceof_server
	./ceof_server

ceof_server: ceof_server.c
	$(CC) -o $@ $^

decrypt: decrypt.c
	$(CC) -o $@ $^

decrypt-test:
	gpg --homedir ~/.ceof/gpg/ --decrypt < ./testcrypt

