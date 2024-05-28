#include "lib.h"

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
run(char* filename, bool bytes, bool lines, bool words)
{
  int is_stdin = filename == NULL;
  FILE* file;
  if (!is_stdin) {
    file = fopen(filename, "r");
    if (file == NULL) {
      fprintf(stderr, "Error: cannot open file %s\n", filename);
      return EXIT_FAILURE;
    }
  } else
    file = stdin;

  counter_t counter = { 0, 0, 0 };
  count(file, &counter);
  print_counter(counter, bytes, lines, words);
  g_print("%s\n", filename ? filename : "");

  if (!is_stdin)
    fclose(file);
  return EXIT_SUCCESS;
}

counter_t
counter_sum(counter_t counter1, counter_t counter2)
{
  counter_t sum = { counter1.lines + counter2.lines,
                    counter1.chars + counter2.chars,
                    counter1.words + counter2.words };
  return sum;
}

void
print_counter(counter_t counter, bool bytes, bool lines, bool words)
{
  if (!bytes && !lines && !words)
    bytes = lines = words = true;
  if (lines)
    g_print("%d ", counter.lines);
  if (words)
    g_print("%d ", counter.words);
  if (bytes)
    g_print("%d ", counter.chars);
}

void
count(FILE* file, counter_t* counter)
{
  char c;
  bool in_word = false;
  while ((c = fgetc(file)) != EOF) {
    counter->chars++;
    if (c == '\n')
      counter->lines++;
    if (c == ' ' || c == '\n' || c == '\t') {
      if (in_word) {
        counter->words++;
        in_word = false;
      }
    } else
      in_word = true;
  }
  if (in_word)
    counter->words++;
}
