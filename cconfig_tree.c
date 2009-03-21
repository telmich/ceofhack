/*******************************************************************************
 *
 * 2008      Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Init a cconfig tree
 *
 */

#include <stdlib.h>              /* NULL                          */
#include <string.h>              /* str*                          */
#include <limits.h>              /* PATH_MAX                      */
#include <dirent.h>              /* opendir                       */
#include <sys/stat.h>            /* stat()                        */

#include "ceofhack.h"            /* cconfig structure             */

int cconfig_tree(struct cconfig *cg)
{
   DIR *dp;
   struct dirent *de;
   char buf[PATH_MAX+1];
   buf[PATH_MAX] = 0;
   struct stat sb;

   /* if path is file: return */
   /* if path is a directory:
    * - add all files to the entry list
    * - call cconfig_tree on all entries
    */
   if(stat(cg->path, &sb) == 0) {
      if(S_ISDIR(sb.st_mode)) { /* get entries */
         cg->noe = 0;
         cg->entries = NULL;

         dp = opendir(cg->path);
         if(!dp) {
            perror(cg->path);
            return 0;
         }

         while((de = readdir(dp)) != NULL) {
            if(de->d_name[0] == '.') continue; /* skip .* */

            cg->entries = realloc(cg->entries, (cg->noe + 1) * sizeof(*cg));
            if(!cg->entries) return 0;

            /* copy path into new node */
            strcpy (cg->entries[cg->noe].path, cg->path);
            strncat(cg->entries[cg->noe].path, "/", PATH_MAX);
            strncat(cg->entries[cg->noe].path, de->d_name, PATH_MAX);

            /* call us recursive */
            if(!cconfig_tree(&cg->entries[cg->noe])) return 0;

            cg->noe++;
        }
        closedir(dp);
      } else { /* no directory */
         cg->noe = -1;
         cg->entries = NULL;
      }
   } else {
      perror(buf);
      return 0;
   }

   return 1;
}
