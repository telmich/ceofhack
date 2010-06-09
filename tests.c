/*******************************************************************************
 *
 * 2009-2010 Nico Schottelius (nico-ceofhack at schottelius.org)
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
 * Test ceofhack
 *
 */


#include <check.h>
#include <stdio.h>

#include <eof.h>

unsigned long eof_id = 42;

START_TEST (t_id)
{
   char buf[EOF_L_ID+1];
   int i;
   int a, b;
   a = 2; b = 2;

   buf[EOF_L_ID] = 0;

   eof_id_init();
   for(i=0; i<1000; i++) {
      eof_id_new(buf);
      printf("id: %s\n", buf);
   }

   fail_unless ((a) == (b), "Not equal");
}
END_TEST

START_TEST (t_eof_id_new)
{
   char buf[EOF_L_ID];
   int a, b;
   a = 2; b = 3;

   eof_id_new(buf);
   printf("id: %s\n", buf);

   fail_unless ((a) == (b), "Not equal");
}
END_TEST

Suite *queue_suite (void)
{
  Suite *s = suite_create ("queue");

  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, t_eof_id_new);
  suite_add_tcase (s, tc_core);

  tcase_add_test (tc_core, t_id);

  return s;
}

int main (void)
{
   int number_failed;

   Suite *s = queue_suite ();
   SRunner *sr = srunner_create (s);

   srunner_run_all (sr, CK_NORMAL);
   number_failed = srunner_ntests_failed (sr);
   srunner_free (sr);
   
   return 0;
}
