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


# create directories
mkdir -p ~/.ceof/transport-protocols/available
mkdir -p ~/.ceof/transport-protocols/enabled/tcp

# copy scripts
cp -r $__abs_mydir/../transport-protocols/tcp-via-netcat \
      ~/.ceof/transport-protocols/available/tcp-via-netcat

# link them
ln -s ~/.ceof/transport-protocols/available/tcp-via-netcat/get \
      ~/.ceof/transport-protocols/enabled/tcp/get
ln -s ~/.ceof/transport-protocols/available/tcp-via-netcat/send \
      ~/.ceof/transport-protocols/enabled/tcp/send