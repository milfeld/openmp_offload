program main
  integer,parameter ::  N = 1024 * 1024 * 128
  integer           ::  i
  real              ::  a=2.0, y(N), x(N), yy(N)

  double precision  :: t0, t1

  !$omp parallel do simd
  do i = 1,N
    x(i)=i/N; y(i)=i/N; yy(i)= i/N
  end do

  call cpu_time(t0)

  !$omp parallel do simd 
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

!! TODO 1 Use the "target loop" construct
!! TODO 2 Use the "target teams distribute parallel do" construct
  !$omp target teams loop  !! 1
!!!$omp target teams distribute parallel do !! 2        gcc poor       0.01994  nv no diff
!!!$omp target teams distribute parallel do simd !! 2b  gcc needs simd 0.007252  nv no diff
!!!$omp target loop  !! 3 ONLY nvidia

!!!$omp target teams distribute  !! 4 broke
!!!$omp parallel do             !! 4 broke
!!!$omp target teams distribute parallel  !! 4 broke
!!!$omp  do                              !! 4 broke
!!!$omp target teams             !! 4  WORKS
!!!$omp distribute parallel do  !! 4  WORKS

    do i = 1,N
       yy(i) = a * x(i) + yy(i)
    end do
! !$omp end target teams distribute parallel do
! !$omp end target teams distribute parallel
! !$omp end distribute parallel do
! !$omp end target teams

  call cpu_time(t1)

!$omp end target data

  write(*,'(" GPU  axpy: ",f11.5," sec ",f8.0," MFLOPS")') t1-t0, 2.0*N*1.0e-6/(t1-t0)

end program
