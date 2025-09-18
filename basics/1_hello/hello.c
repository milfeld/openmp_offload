//                                               Kent Milfeld 5/19/25
#include <stdio.h>

// TODO 1: Add appropriate header file for OMP functions & parameters


int main(){
  printf(" Number of available devices %d\n",omp_get_num_devices());

  // TODO 2: Use target construct to execute omp_is_initial_device on device
  //         omp_is_initial_device returns 0 (true) on host
  //                                       1 (false) on device

  {
    printf(" Ran on GPU (0=true,1=false) %d\n", \
             omp_is_initial_device());
  }
}
