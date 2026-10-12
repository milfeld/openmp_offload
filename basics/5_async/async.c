#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N (1 << 20)  // 1024 * 1024

int main(){
  float a=2.0, y[N], x[N];
  int   n, ndev, ib, ie;

  #pragma omp parallel for simd
  for( int i=0; i<N; i++){ x[i]=i; y[i]=i;}

// TODO_1 Use OpenMP routine to get number of GPUs
  ndev=
  n = N/ndev;

// TODO_2 Set up a parallel region and have
//        a master thread (as a separate construct) 
//        execute the {...} block.
//        Use the num_threads clause to use ndev threads.
  #pragma omp ...
  #pragma omp master
  {
    for(int id=0; id<ndev; id++)
    {                       //simple,unblanced partiting
       ib = id*n; ie = ib+n;
       if(id==ndev-1){ ie=N; n=N-ib;} //final iteration
// TODO_3 Include  nowait and device(<device id>) clauses
       #pragma omp target teams distribute parallel for map(y[ib:n],x[ib:n])
         for(int i=ib; i< ie; i++){ y[i] = a * x[i] + y[i]; }
     }
  }// parallel barrier waits for tasks to complete

  // Note: #pragma omp taskwait // do this if you don't use parallel master

 for(int i=0; i< N; i++)if(y[i]!=a*i+i) 
    printf(" FAILED at: %d val=%f expected %f\n",i,y[i],a*i+i);
 printf("PASSED\n");

 return 0;
}
