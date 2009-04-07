/*
 *  convert.c -- Converts a (unsigned) long into a string
 *  Copyright (C) 2006    René Nussbaumer, Nico Schottelius
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <unistd.h>

#ifdef DEBUG
#include <string.h>
#endif

#define EOUTOFRANGE     (1 << 1);
#define EBUFFERTOOSMALL (1 << 2);

static const char mapping[] = "0123456789abcdef";

static void reverse(char* s) {
    char *start, *end;
    char buf[2];

    start = end = s;

    while(*end++);

    end -= 2;

    while(start < end) {
        buf[0] = *start;
        buf[1] = *end;

        *start = buf[1];
        *end   = buf[0];

        end--;
        start++;
    }
}

static void convert(unsigned long value, unsigned int base, char* converted, size_t size) {
    unsigned int i = 0;

    for(i = 0; i < size; ++i)
        converted[i] = 0;

    i = 0;

    do {
        converted[i++] = mapping[value % base];
        value /= base;
    } while(value);

    reverse(converted);
}

static int boundary(unsigned int base, size_t size, int typesize) {
    if(base < 2 || base > sizeof(mapping))
        return -EOUTOFRANGE;

    if(size < (typesize * 8) + 1)
        return -EBUFFERTOOSMALL;

    return 0;
}

int ultostr(unsigned long value, unsigned int base, char* converted, size_t size) {
    int i;

    if((i = boundary(base, size, sizeof(value))))
        return i;

    convert(value, base, &(converted[0]), size);

    return 0;
}

int ltostr(long value, unsigned int base, char* converted, size_t size) {
    int i;

    if((i = boundary(base, size, sizeof(value))))
        return i;

    if(value >> (sizeof(value) * 8 - 1) && base == 10) {
       converted[i++] = '-';
       value = ~value + 1;
    }

    convert((unsigned long)value, base, &(converted[i]), size - i);

    return 0;
}

#ifdef DEBUG
int main() {
    unsigned long a = 123456;
    long b = -423;
    unsigned int bases[] = {10, 16, 2, 8};
    char buf[(sizeof(long)*8)+1];
    int i;

    for(i = 0; i < sizeof(bases); ++i) {
        if(!ultostr(a, bases[i], buf, sizeof(buf))) {
            write(2, buf, strlen(buf));
            write(2, "\n", 1);
        }
        if(!ltostr(b, bases[i], buf, sizeof(buf))) {
            write(2, buf, strlen(buf));
            write(2, "\n", 1);
        }
    }

    return 0;
}
#endif

