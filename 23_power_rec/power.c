#include <stdio.h>
#include <stdlib.h>
#include "power.h"

unsigned powerhelper(unsigned x, unsigned y, unsigned ans){
  if(y==0) {
    return ans;
  }
  return powerhelper(x, y-1, x*ans);
}

unsigned power(unsigned x, unsigned y){
  return powerhelper(x,y,1);
}
