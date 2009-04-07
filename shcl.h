#ifndef SHCL_H
#define SHCL_H

/* header for shcl: should be merged back later */
void reverse(char* s);
void convert(unsigned long value, unsigned int base, char* converted, size_t size);
int boundary(unsigned int base, size_t size, size_t typesize);
int ultostr(unsigned long value, unsigned int base, char* converted, size_t size);
int ltostr(long value, unsigned int base, char* converted, size_t size);

#endif
