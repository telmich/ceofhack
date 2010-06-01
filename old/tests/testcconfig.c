#include "ceofhack.h"


int main(int argc, char **argv)
{
   struct cconfig cg;
   cconfig_tree(argv[1], &cg);

   return 0;
}
