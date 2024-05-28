#include <stdbool.h>
#include <stdio.h>

typedef struct counter
{
  int lines;
  int chars;
  int words;
} counter_t;

counter_t counter_sum (counter_t counter1, counter_t counter2);
void print_counter (counter_t counter, bool bytes, bool lines, bool words);
void count (FILE *file, counter_t *counter);
int run (char *filename, bool bytes, bool lines, bool words);
