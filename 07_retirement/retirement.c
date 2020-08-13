#include <stdlib.h>
#include <stdio.h>

typedef struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
} retire_info;

double final(double initial, double contribution, double rate){
  double final;
  final = initial*(1+rate) + contribution;
  return final;
}

void retirement (int startAge,double initial,retire_info working,retire_info retired){
  double balance = initial;
  for(int i= startAge;i<startAge+working.months;i++){
    int ageyear = i/12 ;
    int agemonth = i%12;
    printf("Age %3d month %2d you have $%.2lf\n",ageyear,agemonth,balance);
    balance = final(balance,working.contribution,working.rate_of_return);
  }
  for(int i = startAge+working.months;i<startAge+working.months+retired.months;i++){
    int ageyear = i/12 ;
    int agemonth = i%12;
    printf("Age %3d month %2d you have $%.2lf\n",ageyear,agemonth,balance);
    balance = final(balance,retired.contribution,retired.rate_of_return);
  }
}

int main(void){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;
  int age =327;
  double initial = 21345;
  retirement (age, initial, working, retired);
  return EXIT_SUCCESS;
}
