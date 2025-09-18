!!                                               Kent Milfeld 5/19/25
program main
  integer,parameter ::  N = 1024 * 1024 * 128
  integer           ::  i
  real              ::  a=2.0, y(N), x(N), yy(N)

  double precision  :: t0, t1

!! TODO_1 workshare this loop on the host (a warm up)

  do i = 1,N
    x(i)=i/N; y(i)=i/N; yy(i)= i/N
  end do

  call cpu_time(t0)

!! TODO_2 workshare this loop on the host --timed for performance
  do i = 1,N
     y(i) = a * x(i) + y(i)
  end do

  call cpu_time(t1)
  write(*,'(" HOST axpy: ",f11.5," sec ",f8.0," MFLOPS")') t1-t0, 2.0*N*1.0e-6/(t1-t0)


!! The next construct puts x and yy on the GPU at the beginning of the block {...}
!!                   and returns yy at the end of the block {...}
!!                   This avoids timing the data transfers, more later on this.
!$omp target data map(to: x) map(tofrom: yy)

  call cpu_time(t0)
!! TODO_3 OFFLOAD: Workshare the loop (with parallel for) and 
!!                 distribute across teams --timed for performance
!! TODO_4 OFFLOAD: Use the loop construct which will automatically
!!                 distribution across teams and run loop iterations
!!                 concurrently--timed for performance.
!! TODO_5 OFFLOAD: experiment with changing the number of
 !!                teams with the  num_teams() clause.


    do i = 1,N
       yy(i) = a * x(i) + yy(i)
    end do
!!!$omp end target teams distribute parallel do  !! don't forget endings
!!!$omp end target teams loop

  call cpu_time(t1)

!$omp end target data

  write(*,'(" GPU  axpy: ",f11.5," sec ",f8.0," MFLOPS")') t1-t0, 2.0*N*1.0e-6/(t1-t0)

end program
