#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n){
  if (n<0){
    return -1;
  }
  if (n==0){
    return 0;
  }
  int mleng = 1;
  int leng = 1;
  for (int i = 1 ; i < n ; i++){
    if (array[i] > array[i-1]){
      leng ++;
      if (leng > mleng){
	mleng = leng;
      }
    }else{
      leng = 1;
    }
  }
  return mleng;
}
