#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 100000 

void d_saxpy(int n, float a, float* x, float* y);

#pragma omp declare variant(d_saxpy) match( construct={dispatch} )
void saxpy(int n, float a, float* x, float* y)
{
  #pragma omp parallel for
  for(int i=0; i<n; i++) y[i]=a*x[i]+y[i];
}

#pragma omp begin declare target
void d_saxpy(int n, float a, float* x, float* y)
{
  #pragma omp target teams distribute parallel for 
  for(int i=0; i<n; i++) y[i]=a*x[i]+y[i];
}
#pragma omp end declare target


int main(){
   float a=2.0;
   float *x=(float *)malloc(N*sizeof(float));
   float *y=(float *)malloc(N*sizeof(float));

   saxpy(N,a,x,y);

   for( int i=0; i<N; i++){x[i]=0.5; y[i]=1.0;}

   #pragma omp target data  map(to: x[0:N]) map(tofrom: y[0:N]) use_device_ptr(x,y)
   {
      #pragma omp dispatch is_device_ptr(x,y)
      saxpy(N,a,x,y);
   }
   for( int i=0; i<N; i++){ 
     if(  abs(y[i]-2.0)>0.000001 ){printf(" ERROR: val=%f (2)\n",y[i]); return 1;}
   }
   printf(" PASS\n");
}
