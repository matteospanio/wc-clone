#include <argp.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

const char *argp_program_version = "wc-clone 0.1";
const char *argp_program_bug_address = "<spanio@dei.unipd.it>";
static char doc[]
    = "Print newline, word and byte counts for each FILE, and a total line if "
      "more than one FILE is specified. A word is a non-zero-length sequence "
      "of characters delimited by a white space.";
static char args_doc[] = "[FILE...]";

static struct argp_option options[] = {
  { "bytes", 'c', 0, 0, "print the byte counts", 0 },
  { "lines", 'l', 0, 0, "print the newline counts", 0 },
  { "words", 'w', 0, 0, "print the word counts", 0 },
  { 0 },
};

typedef struct arguments
{
  bool bytes;
  bool lines;
  bool words;
  GList *files;
} args_t;

static void print_list (GList *list) __attribute_maybe_unused__;

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  args_t *arguments = state->input;
  switch (key)
    {
    case 'c':
      arguments->bytes = true;
      break;
    case 'l':
      arguments->lines = true;
      break;
    case 'w':
      arguments->words = true;
      break;
    case ARGP_KEY_ARG:
      arguments->files = g_list_append (arguments->files, arg);
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
        arguments->files = NULL;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

static void
print_list (GList *list)
{
  if (list == NULL)
    return;
  printf ("%s ", (char *)list->data);
  print_list (list->next);
}

int
main (int argc, char **argv)
{
  args_t arguments = { 0 };
  int result;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.files != NULL)
    {
      GList *l;
      for (l = arguments.files; l != NULL; l = l->next)
        {
          result = run (l->data, arguments.bytes, arguments.lines,
                        arguments.words);
        }
      g_list_free (arguments.files);
    }
  else
    {
      result = run (NULL, arguments.bytes, arguments.lines, arguments.words);
    }

  exit (result);
}
