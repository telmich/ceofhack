LDFLAGS= $(shell gpgme-config --libs)

all: decrypt
ceof_server_exec: ceof_server
	./ceof_server

ceof_server: ceof_server.c
	gcc -g -D_FILE_OFFSET_BITS=64 -lgpgme -Wall -o $@ $^

decrypt:
	gpg --homedir ~/.ceof/gpg/ --decrypt < ./testcrypt

