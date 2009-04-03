#!/bin/bash -e
# 
# 2008      Nico Schottelius (nico-ceofhack at schottelius.org)
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

#
# Standard variables (stolen from cconf)
#
__pwd="$(pwd -P)"
__mydir="${0%/*}"; __abs_mydir="$(cd "$__mydir" && pwd -P)"
__myname=${0##*/}; __abs_myname="$__abs_mydir/$__myname"

if ! $__abs_mydir/gen_key.sh; then
	echo "key generation failed" 1>&2
	exit 1
fi

# install the listener 
install -D -m 0755 $__abs_mydir/../tp/tcp/c/listen \
        ~/.ceof/transport-protocols/available/tcp/listen
# install the sender
install -D -m 0755 $__abs_mydir/../tp/tcp/bash-netcat/send \
      ~/.ceof/transport-protocols/available/tcp/send

echo "done."

