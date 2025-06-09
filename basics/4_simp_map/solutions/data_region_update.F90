
program main
   integer,parameter :: N=1024*1024
   double precision  :: v1(N), v2(N), p(N)

   do i=1,N; v1(i)=i; v2(i)=i; p(i)=0.0d0; enddo

!! TODO 1: Create a target data region around the two offloads, and
!!         for v1 and v2 with map type to, and p with tofrom.
   !$omp target data map(to:v1,v2) map(tofrom:p)

      !$omp target teams distribute parallel do
      do i=1,N; p(i) = v1(i) + v2(i); end do

      do i=1,N; v1(i) = (N-i+1); enddo
!! TODO 2: Update v1 values on device
      !$omp target update to(v1)

      !$omp target teams distribute parallel do
       do i=1,N; p(i) = p(i) + (v1(i) + v2(i)); end do

   !$omp end target data
   write(*,'("(p(1)/exact):(p(N)/exact) = (",F9.1,"/",i9,") : (",F9.1,"/",i9,")")') &
            p(1),2+(N+1),p(n),2*N+(N+1)
end program
