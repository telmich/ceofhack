/*******************************************************************************
 *
 * 2009     A. Pic. (eofdev at apic.name)
 *
 * This file is part of ceofhack.

 * ceofhack is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ceofhack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ceofhack.  If not, see <http://www.gnu.org/licenses/>.

 *
 * Wrapper for write() that continues on EINTR / incomplete write
 *
 */

#include <unistd.h>     /* write          */
#include <errno.h>      /* EINTR          */

ssize_t write_all(int fd, const void *buf, size_t count)
{
        size_t written=0;
        while(written < count) {
                ssize_t n = write(fd, buf+written, count-written);
                if(n<0 && errno == EINTR)
                        continue;
                if(n<=0)
                        return n;
                written += n;
        }
        return written;
}

