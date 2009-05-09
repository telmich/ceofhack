#!/bin/sh

gpgdir="$HOME/.ceof/gpg"

if [ -e "$gpgdir/secring.sec" ]; then
	exit 0
fi

if [ ! -x "`which gpg`" ]; then
	echo "gpg not found" 1>&2
	exit 1
fi

mkdir -p "$gpgdir" || exit 1
cd "$gpgdir" || exit 1

cat > keygen.batch << EOF
	%echo Generating a standard key
	Key-Type: DSA
	Key-Length: 1024
	Subkey-Type: ELG-E
	Subkey-Length: 1024
	Name-Real: $USER
	Name-Comment: EOF
	Expire-Date: 0
	%commit
	%echo done
EOF

gpg --homedir "$gpgdir" --batch --gen-key keygen.batch || exit 1

exit 0

