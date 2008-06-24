ceof_server: ceof_server.c
	gcc -D_FILE_OFFSET_BITS=64 -lgpgme -Wall -o $@ $^
