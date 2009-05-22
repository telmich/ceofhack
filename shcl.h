#ifndef SHCL_H
#define SHCL_H


/* header for shcl: should be merged back later */

#include <sys/types.h>

void reverse(char* s);
void convert(unsigned long value, unsigned int base, char* converted, size_t size);
int boundary(unsigned int base, size_t size, size_t typesize);
int ultostr(unsigned long value, unsigned int base, char* converted, size_t size);
int ltostr(long value, unsigned int base, char* converted, size_t size);

ssize_t write_all(int fd, const void *buf, size_t count);
ssize_t read_all(int fd, void *buf, size_t count);

int fileexists(char *filename);
int openwriteclose(char *fn, char buf[], int len);


#endif
