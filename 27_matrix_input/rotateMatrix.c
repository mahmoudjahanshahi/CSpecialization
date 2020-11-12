#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]);

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char tmp[12];
  int row = 0;
  while (fgets(tmp, 12, f) != NULL) {
    if (strchr(tmp, '\n') == NULL) {
      printf("Line is too long!\n");
      return EXIT_FAILURE;
    }
    if (strchr(tmp, '\0') != &tmp[11]) {
      printf("Line is too short!\n");
      return EXIT_FAILURE;
    }
    for (int j = 0; j < 10; j++) {
      matrix[row][j] = tmp[j];
    }
    row++;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (row != 10) {
    perror("Wrong number of rows!");
    return EXIT_FAILURE;
  }
  rotate(matrix);
  for (int i = 0; i < 10;i++) {
    for (int j = 0; j < 10;j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
