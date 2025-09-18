!!                                               Kent Milfeld 5/19/25
program main

  !! TODO 1: Add appropriate "use" statement for OMP functions


  implicit none
  print*, "Number of available devices ", omp_get_num_devices()

  !! TODO 2: Use target construct to execute omp_is_initial_device on device
  !!         omp_is_initial_device returns T when on host, F when on device

     print*, "Ran on GPU (T|F): ", .not.omp_is_initial_device()


end program
