!!                                               Kent Milfeld 5/19/25
program main
  use omp_lib
  integer,parameter :: NT=1024*1024
  real    ::  a=2.0, y(NT), x(NT)
  integer ::  n, ndev, ib, ie

  !$omp parallel do simd
  do i=1,NT; x(i)=i; y(i)=i; enddo

!! USE 1 GPU and multiple executions with MPS
!! TODO_1 assign ndev to some small number (e.g. 3)
  ndev=omp_get_num_devices()
  n = NT/ndev


!! TODO_2 remove the parallel and master regions
!!        Just throw the tasks on the queue
  !$omp parallel num_threads(ndev)
  !$omp master
    do id=0, ndev-1
                             !partitioning: simple,unblanced
      ib = 1 + id*n; ie = ib + n - 1
      if(id == ndev-1) then; ie=NT; endif !!final iter.

!! TODO_3 set the argument of device() clause to 0.
      !$omp target teams distribute parallel do map(y(ib:ie),x(ib:ie)) &
      !$omp&       nowait device(id)
         do i=ib, ie;  y(i) = a * x(i) + y(i); enddo

    enddo
  !$omp end master 
  !$omp end parallel !! parallel barrier waits for tasks to complete

  !! Can do independent CPU work HERE

!! TODO_4 wait for the tasks to finish with a taskwait directive.

  !! Can reuse x and y here, after taskwait.

  do i=1,NT 
    if(y(i) /= a*i+i) print*," FAILED at:",i," expected ",a*i+i,"found ",y(i)
  enddo
  print*,"PASSED"

end program
