#include <check.h>

START_TEST (test_money_create)
{
   int a, b;

   a = 2; b = 3;

   fail_unless ((a) == (b), "Not equal");
}
END_TEST

Suite *money_suite (void)
{
  Suite *s = suite_create ("Money");

/* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_money_create);
  suite_add_tcase (s, tc_core);

  return s;
}

int main (void)
{
   int number_failed;
   Suite *s = money_suite ();
   SRunner *sr = srunner_create (s);
   srunner_run_all (sr, CK_NORMAL);
   number_failed = srunner_ntests_failed (sr);
   srunner_free (sr);
  return 0;
}
