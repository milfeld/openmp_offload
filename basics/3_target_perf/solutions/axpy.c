#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N (1 << 27)  // 1024 * 1024 * 1024/2^3

int main(){
  float a=2.0, y[N], x[N], yy[N];

  struct timespec rt[2]; //timer
  double wt; 
// TODO_1 workshare this loop on the host (a warm up)
  #pragma omp parallel for simd  
  for( int i=0; i<N; i++){
  x[i]=(float)i/N; y[i]=(float)i/N; yy[i]= (float)i/N; }

  clock_gettime(CLOCK_REALTIME, rt + 0);

// TODO_2 workshare this loop on the host --timed for performance
  #pragma omp parallel for simd
    for (int i = 0; i < N; i++) { y[i] = a * x[i] + y[i]; }

  clock_gettime(CLOCK_REALTIME, rt + 1);

  wt = (rt[1].tv_sec-rt[0].tv_sec) + 1.0e-9*(rt[1].tv_nsec-rt[0].tv_nsec);
  printf(" HOST axpy: %11.5f sec %8.0f MFLOPS\n", wt, 2.0*N*1.0e-6/wt);


// NOTE: The next construct puts x and yy on the GPU at the beginning of the block {...}
//                   and returns yy at the end of the block {...}
//                   This avoids timing the data transfers, more later on this.

#pragma omp target data map(to: x) map(tofrom: yy)
{

  clock_gettime(CLOCK_REALTIME, rt + 0);

// TODO_3 OFFLOAD: Workshare the loop (with parallel for) and 
//                 distribute across teams --timed for performance
// TODO_4 OFFLOAD: Use the loop construct which will automatically
//                 distribution across teams and run loop iterations
//                 concurrently--timed for performance.
// TODO_5 OFFLOAD: experiment with changing the number of
//                 teams with the  num_teams() clause.

//  #pragma omp target teams distribute parallel for               // TODO3
    #pragma omp target teams distribute parallel for num_teams(1024) // TODO5
//  #pragma omp target teams loop                     // TODO4

    for (int i = 0; i < N; i++) { yy[i] = a * x[i] + yy[i]; }

  clock_gettime(CLOCK_REALTIME, rt + 1);

}
  wt = (rt[1].tv_sec-rt[0].tv_sec) + 1.0e-9*(rt[1].tv_nsec-rt[0].tv_nsec);
  printf("  GPU axpy: %11.5f sec %8.0f MFLOPS\n", wt, 2.0*N*1.0e-6/wt);

  return 0;
}
