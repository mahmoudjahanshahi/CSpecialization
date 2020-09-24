#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y) ;

void run_check(unsigned x, unsigned y, unsigned ans){
  unsigned res = power(x,y);
  if (res != ans ){
    printf("%d to the power of %d should result in %d, but the implementation resulted in %d! \n", x, y, ans, res);
    exit(EXIT_FAILURE);
  }
}

int main(void){
  run_check(3,4,81);
  run_check(0,0,1);
  run_check(0,4,0);
  run_check(-1,1,-1);
  return EXIT_SUCCESS;
}
  
