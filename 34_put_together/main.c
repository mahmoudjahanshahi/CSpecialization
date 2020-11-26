#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t* countFile = createCounts();
  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  char* line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    char* newLine = strchr(line, '\n');
    *newLine = '\0';
    char* name = lookupValue(kvPairs, line);
    addCount(countFile, name);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return countFile;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    perror("Too few input arguments!");
    return EXIT_FAILURE;
  }
  kvarray_t* kv = readKVs(argv[1]);
  for (size_t i = 2; i < argc; i++) {
    counts_t* c = countFile(argv[i], kv);
    char* outName = computeOutputFileName(argv[i]);
    FILE* f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    printCounts(c, f);
    freeCounts(c);
    free(outName);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
