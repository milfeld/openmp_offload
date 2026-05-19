#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void d_saxpy(int n, float a, float* x, float* y);

#pragma omp declare variant(d_saxpy) match( construct={dispatch} )
void saxpy(int n, float a, float* x, float* y)
{
  printf(" saxpy\n");
  #pragma omp parallel for
  for(int i=0; i<n; i++) y[i]=9*y[i];
}

void d_saxpy(int n, float a, float* x, float* y)
{
    printf(" d_saxpy\n");
    #pragma omp target teams distribute parallel for is_device_ptr(x,y)
    for(int i=0; i<n; i++) y[i]=a*x[i]+y[i];
}

#define N 100000 
void    saxpy(int n, float a, float* x, float* y);
void  d_saxpy(int n, float a, float* x, float* y);

int main(){
   float a=2.0;
   float *x=(float *)malloc(N*sizeof(float));
   float *y=(float *)malloc(N*sizeof(float));

   saxpy(N,a,x,y);

   for( int i=0; i<N; i++){x[i]=0.5; y[i]=1.0;}

   #pragma omp target data  map(to: x[0:N]) map(tofrom: y[0:N]) use_device_ptr(x,y)
   {
     #pragma omp dispatch
     saxpy(N,a,x,y);
   }

   for( int i=0; i<N; i++){ 
     if(  fabs(y[i]-2.0)>0.000001 ){printf(" ERROR: val=%f (2)\n",y[i]); return 1;}
   }
   printf(" PASS\n");
}
