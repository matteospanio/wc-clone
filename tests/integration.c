#include <glib.h>

#include "src/lib.h"

static void
test_invalid_file(void)
{
  if (g_test_subprocess()) {
    int result = run("invalid_file", true, true, true);
    exit(result);
  } else {
    g_test_trap_subprocess(NULL, 0, 0);
    g_test_trap_assert_failed();
    g_test_trap_assert_stderr("Error: cannot open file invalid_file\n");
  }
}

int
main(int argc, char* argv[])
{
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/integration/run", test_invalid_file);

  return g_test_run();
}
