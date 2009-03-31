#!/bin/sh

if [ -e ~/.ceof/pgp/eof.sec ]; then
	exit 0
fi

if [ ! -x "`which gpg`" ]; then
	echo "gpg not found" 1>&2
	exit 1
fi

mkdir -p ~/.ceof/pgp || exit 1
cd ~/.ceof/pgp || exit 1

cat > keygen.batch << EOF
	%echo Generating a standard key
	Key-Type: DSA
	Key-Length: 1024
	Subkey-Type: ELG-E
	Subkey-Length: 1024
	Name-Real: $USER
	Name-Comment: EOF
	Expire-Date: 0
        %pubring eof.pub
        %secring eof.sec
	%commit
	%echo done
EOF

gpg --batch --gen-key keygen.batch || exit 1

exit 0

