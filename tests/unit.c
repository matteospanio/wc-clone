#include <glib.h>

#include "src/lib.h"

static void
test_counter_sum(void)
{
  counter_t counter1 = { 0, 0, 0 };
  counter_t counter2 = { 0, 0, 0 };

  counter_t result;
  result = counter_sum(counter1, counter2);

  g_assert_cmpint(result.lines, ==, 0);
  g_assert_cmpint(result.words, ==, 0);
  g_assert_cmpint(result.chars, ==, 0);

  counter1 = (counter_t){ 1, 2, 3 };
  counter2 = (counter_t){ 4, 5, 6 };

  result = counter_sum(counter1, counter2);

  g_assert_cmpint(result.lines, ==, 5);
  g_assert_cmpint(result.words, ==, 9);
  g_assert_cmpint(result.chars, ==, 7);
}

static void
test_print_counter(void)
{
  if (g_test_subprocess()) {
    counter_t counter = { 1, 2, 3 };
    print_counter(counter, true, true, true);

    exit(0);
  } else {
    g_test_trap_subprocess(NULL, 0, 0);
    g_test_trap_assert_passed();
    g_test_trap_assert_stdout("1 3 2 ");
  }
}

int
main(int argc, char* argv[])
{
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/unit/counter/sum", test_counter_sum);
  g_test_add_func("/unit/counter/print", test_print_counter);

  return g_test_run();
}
