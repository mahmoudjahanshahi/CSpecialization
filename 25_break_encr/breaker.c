#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void countChars(FILE * f, int* counts) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c %= 26;
      counts[c] += 1;
    }
  }
}

int arrayMax(int* array) {
  int largest = array[0];
  int index = 0;
  for (int i = 1; i < 26; i++) {
    if (array[i] > largest) {
      largest = array[i];
      index = i;
    }
  }
  return index;
}

void decrypt(int n) {
  int key;
  int diff = n - 23;
  if (diff >= 0) {
    key = diff;
  }
  else {
    key = 26 + diff;
  }
  printf("%d\n", key);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int counts[26] = { 0 };
  countChars(f, counts);
  int max = arrayMax(counts);
  decrypt(max);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
