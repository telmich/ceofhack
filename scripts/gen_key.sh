#!/bin/sh
# 
# 2009      Nico Schottelius (nico-ceofhack at schottelius.org)
# 
# This file is part of ceofhack.
#
# ceofhack is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ceofhack is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ceofhack. If not, see <http://www.gnu.org/licenses/>.
#

gpgdir="$HOME/.ceof/gpg"

# gpg wants a secure directory
umask 077

[ -e "$gpgdir/secring.gpg" ] && exit 0

if [ ! -x "`which gpg`" ]; then
	echo "gpg not found" 1>&2
	exit 1
fi

set -e

mkdir -p "$gpgdir"
cd "$gpgdir"

cat > keygen.batch << EOF
	%echo Generating a standard key
	Key-Type: DSA
	Key-Length: 1024
	Subkey-Type: ELG-E
	Subkey-Length: 1024
	Name-Real: $USER
	Name-Comment: EOF-2
	Expire-Date: 0
	%commit
	%echo done
EOF

gpg --homedir "$gpgdir" --batch --gen-key keygen.batch

exit 0
