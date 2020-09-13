#include<stdio.h>
#include<stdlib.h>
#include"maxSeq.h"

int main(void){
  int myArray[] = {-2,-1,0,1,-1,6};
  if ( maxSeq(myArray,6) != 4) return EXIT_FAILURE;
  printf("OK1\n");
  int myArray2[] = {6};
  if ( maxSeq(myArray2,1) != 1) return EXIT_FAILURE;
  printf("OK2\n");
  int myArray3[] = {};
  if ( maxSeq(myArray3,0) != 0) return EXIT_FAILURE;
  printf("OK3\n");
  int myArray4[] = {1,125,633,2,2,5,7,9,10};
  if ( maxSeq(myArray4,9) != 5) return EXIT_FAILURE;
  printf("OK4\n");
  return EXIT_SUCCESS;
}
