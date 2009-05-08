#!/bin/sh
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

set -e

######### transport protocols
###### tcp
echo "Adding transport protocol tcp"
install -D -m 0755 $__abs_mydir/../tp/tcp/c3/listen \
        ~/.ceof/transport-protocols/available/tcp/listen
install -D -m 0755 $__abs_mydir/../tp/tcp/bash-netcat/send \
      ~/.ceof/transport-protocols/available/tcp/send
###### enable tcp listening: 0.0.0.0:4242
echo "Enabling listing on $(cat $__abs_mydir/../tp/tcp/example_url)"
install -d -m 0755 ~/.ceof/transport-protocols/listen/tcpv4-any-4242
install -m 0644 $__abs_mydir/../tp/tcp/example_url    \
         ~/.ceof/transport-protocols/listen/tcpv4-any-4242/url

###### dummy: only for development
if [ "$1" = "dev" ]; then

   install -d -m 0755 ~/.ceof/transport-protocols/available/dummy
   install -m 0755 $__abs_mydir/../tp/dummy/c/send    \
                   $__abs_mydir/../tp/dummy/c/listen  \
            ~/.ceof/transport-protocols/available/dummy

   install -d -m 0755 ~/.ceof/transport-protocols/listen/dummy-for-dev
   install -m 0644 $__abs_mydir/../tp/dummy/example_url    \
            ~/.ceof/transport-protocols/listen/dummy-for-dev/url
fi

echo "done."

