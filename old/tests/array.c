
struct a {
   int b;
   char foo[5];
};

int main() {

   struct a z[] = {
      { 1, "baa" },
      { 2, "foo" }
   };

   struct a y[][] = { { { 1, "baa" }, { 2, "foo" } }, { { 1, "baa" }, { 2, "foo" } } };

   z[1].b = z[0].b;

   y[0][1].b = y[1][1].b;

   return 1;
}
