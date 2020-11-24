#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

char* getKey(char* line) {
  char* key;
  char* equalSign = strchr(line, '=');
  *equalSign = '\0';
  key = line;
  return key;
}

char* getValue(char* line) {
  char* value;
  char* nullTer = strchr(line, '\0');
  value = nullTer + 1;
  char* newLine = strchr(value, '\n');
  *newLine = '\0';
  return value;
}

kvarray_t * readKVs(const char * fname) {
  FILE* f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  kvarray_t* kvarray = malloc(sizeof(* kvarray));
  kvarray->kvCount = 0;
  kvarray->kv = NULL;
  char* line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    kvpair_t* kvpair = malloc(sizeof(*kvpair));
    kvpair->key = getKey(line);
    kvpair->value = getValue(line);
    kvarray->kv = realloc(kvarray->kv, (kvarray->kvCount + 1) * sizeof(*kvarray->kv));
    kvarray->kv[kvarray->kvCount] = kvpair;
    line = NULL;
    kvarray->kvCount++;
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->kvCount; i++) {
    free(pairs->kv[i]->key);
    free(pairs->kv[i]);
  }
  free(pairs->kv);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->kvCount; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kv[i]->key, pairs->kv[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->kvCount; i++) {
    if (strcmp(pairs->kv[i]->key,key) == 0) {
      return pairs->kv[i]->value;
    }
  }
  return NULL;
}
