#!/bin/sh

cat eof.h | awk '/^#define EOF_L_/ { print $2 "=" $3 } '
