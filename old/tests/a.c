#include <stdio.h>

int c=2;
int d=3;

b()
{
   return (c < d) ? c++ : -1;
}

int main()
{
   int a=b();
   printf("a=%d\n", a);
   printf("c=%d\n", c);
}
