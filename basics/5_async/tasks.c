#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N (1 << 20)  // 1024 * 1024

int main(){
  float a=2.0, y[N], x[N];
  int   n, ndev, ib, ie;

  #pragma omp parallel for simd
  for( int i=0; i<N; i++){ x[i]=i; y[i]=i;}

// USE 1 GPU and multiple executions with MPS
// TODO_1 assign ndev to some small number (e.g. 3)
  ndev=omp_get_num_devices();
  n = N/ndev;

// TODO_2 remove the parallel and master regions
//        Just throw the tasks on the queue
  #pragma omp parallel num_threads(ndev)
  #pragma omp master
  {

    for(int id=0; id<ndev; id++)
    {                       //simple,unblanced partiting
       ib = id*n; ie = ib+n;
       if(id==ndev-1){ ie=N; n=N-ib;} //final iteration

// TODO_3 set the argument of device() clause to 0.
       #pragma omp target teams distribute parallel for \
                  nowait device(id) map(y[ib:n],x[ib:n])
         for(int i=ib; i< ie; i++){ y[i] = a * x[i] + y[i]; }
     }

   } //end of master (and parallel)

//   Can do independent CPU work HERE

// TODO_4 wait for the tasks to finish with a taskwait directive


//   Can reuse x and y here after taskwait.

 for(int i=0; i< N; i++)if(y[i]!=a*i+i) 
    printf(" FAILED at: %d val=%f expected %f\n",i,y[i],a*i+i);
 printf("PASSED\n");

 return 0;
}
