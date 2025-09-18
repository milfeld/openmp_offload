!!                                               Kent Milfeld 5/19/25
program main
  use omp_lib
  integer,parameter :: NT=1024*1024
  real    ::  a=2.0, y(NT), x(NT)
  integer ::  n, ndev, ib, ie

  !$omp parallel do simd
  do i=1,NT; x(i)=i; y(i)=i; enddo

!! TODO_1 Use OpenMP routine to get number of GPUs
  ndev=
  n = NT/ndev


!! TODO_2 Set up a parallel region and have the
!!        a master thread (as a separate construct) 
!!        execute the the "do id" loop
!!        Use the num_threads clause to use ndev threads.
  !$omp 
  !$omp 
    do id=0, ndev-1
                             !partitioning: simple,unblanced
      ib = 1 + id*n; ie = ib + n - 1
      if(id == ndev-1) then; ie=NT; endif !!final iter.

!! TODO_3 Include nowait and device(<device id>) clauses
      !$omp target teams distribute parallel do map(y(ib:ie),x(ib:ie))
      do i=ib, ie  
         y(i) = a * x(i) + y(i)
      enddo

    enddo
  !$omp end master 
  !$omp end parallel

  !Note: !$omp taskwait !! do this if you don't use parallel master

  do i=1,NT 
    if(y(i) /= a*i+i) print*," FAILED at:",i," expected ",a*i+i,"found ",y(i)
  enddo
  print*,"PASSED"

end program
