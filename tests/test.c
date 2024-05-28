#include <glib.h>
#include <locale.h>

#include "src/lib.h"

typedef struct
{
  counter_t counter;
} Fixture;

static void
setup (Fixture *fixture, gconstpointer user_data)
{
  fixture->counter.lines = 0;
  fixture->counter.chars = 0;
  fixture->counter.words = 0;
}

static void
test_counter_sum (Fixture *fixture, gconstpointer user_data)
{
  counter_t result;
  result = counter_sum (fixture->counter, fixture->counter);

  g_assert_cmpint (result.lines, ==, 0);

  fixture->counter.lines = 1;
  result = counter_sum (fixture->counter, fixture->counter);

  g_assert_cmpint (result.lines, ==, 2);
}

int
main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");

  g_test_init (&argc, &argv, NULL);

  g_test_add ("/counter/sum", Fixture, NULL, setup, test_counter_sum, NULL);

  return g_test_run ();
}
