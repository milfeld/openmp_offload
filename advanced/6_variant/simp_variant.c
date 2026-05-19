#include <stdio.h>
#include   <omp.h>

void d_fun(void);
//                 use this v---v  when  v--------------v
#pragma omp declare variant(d_fun)   match(construct={dispatch})
void fun(){                                 //< base function
  printf("   fun: ON_HOST=%c T=true\n", \
        (omp_is_initial_device()==0) ? 'T':'F');
}

// use this variant when found is in a dispatch construct
void d_fun(){
  #pragma omp target
  printf(" d_fun: ON_DEV =%c T=true\n", \
        (omp_is_initial_device()==0) ? 'T':'F');
}


int main(){
  fun();              // No dispatch context, uses base, fun().

  #pragma omp dispatch
  fun();              // In dispatch construct, executes d_fun().
}
