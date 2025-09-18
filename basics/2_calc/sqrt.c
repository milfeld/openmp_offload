//                                               Kent Milfeld 5/19/25
# define TOL 1.0e-5
# define N 1024*1024*8
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fun(float a, float *x){
   for(int i=0; i<N; i++)
     x[i]=sqrt(a*i*i);
}

int main(){
  float a=3.0, x[N];

  // TODO_1 Run this function on a GPU

  fun(a,x);

  for(int i=0; i<N; i++) 
    if( fabs(x[i]-sqrt(a*i*i))/sqrt(a*i*i) > TOL ){
        printf(" FAILED at function %d %f %f\n",i,x[i],sqrt(a*i*i));
        exit(1);
    }
  printf(" Device function passed\n");


  // TODO_2 Run this block of code on a GPU


    for(int i=0; i<N; i++)
     x[i]=sqrt(a*i*i);


  for(int i=0; i<N; i++) 
    if( fabs(x[i]-sqrt(a*i*i))/sqrt(a*i*i) > TOL ){
        printf(" FAILED at block %d %f %f\n",i,x[i],sqrt(a*i*i));
        exit(1);
    }
  printf(" Device block passed\n");

}
