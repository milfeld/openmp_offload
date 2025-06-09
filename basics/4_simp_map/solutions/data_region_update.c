#include <stdio.h>
#define N 1024*1024
int main(){
   double v1[N], v2[N], p[N];
   for (int i=0; i<N; i++){ 
      v1[i]=(double)i; v2[i]=(double)i; p[i]=0.0e0;
   } 

// TODO 1: Create a target data region around the two offloads
//         for v1 and v2 with map type to, and p with tofrom.
   #pragma omp target data map(to:v1,v2) map(tofrom:p)
   {
      #pragma omp target teams distribute parallel for
      for (int i=0; i<N; i++) p[i] = v1[i] + v2[i];

      for (int i=0; i<N; i++) v1[i] = (double)(N-i-1);
// TODO 2: Update v1 values on device
//    #pragma omp target update to(v1)

      #pragma omp target teams distribute parallel for
      for (int i=0; i<N; i++)
        p[i] = p[i] + (v1[i] + v2[i]);
   }
   printf("(p[%d] and p[%d])  %f =? %d, %13.0f =? %d\n",0,N-1, p[0],N-1,p[N-1],(N-1)*3);
}
