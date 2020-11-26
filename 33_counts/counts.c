#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t* counts = malloc(sizeof(*counts));
  counts->array = NULL;
  counts->size = 0;
  counts->unknown = 0;
  return counts;
}

int findCount(counts_t* c, const char* name) {
  for (int i = 0; i < c->size; i++) {
    if (strcmp(c->array[i]->string, name) == 0) {
      return i;
    }
  }
  return -1;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown++;
    return;
  }
  int index = findCount(c, name);
  if (index > -1) {
    c->array[index]->count++;
    return;
  }
  one_count_t* one_count = malloc(sizeof(*one_count));
  one_count->string = name;
  one_count->count = 1;
  c->array = realloc(c->array, (c->size + 1) * sizeof(*c->array));
  c->array[c->size] = one_count;
  c->size++;
}

void printCounts(counts_t * c, FILE * outFile) {
  FILE* f = outFile;
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->size; i++) {
    fprintf(f, "'%s': %d\n", c->array[i]->string, (int)c->array[i]->count);
  }
  if (c->unknown > 0) {
    fprintf(f, "<unknown>: %d\n", (int)c->unknown);
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
