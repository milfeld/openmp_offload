!!                                               Kent Milfeld 5/19/25
program main
  integer, parameter :: N=1024*1024*8
  real :: TOL=1.0E-6, a=3.0, x(N)

  do i = 1,N
    x(i)=sqrt(a*i*i)  !! init
  end do

  !! TODO_1 Run this function on a GPU

    call fun(a,x)

  call check(x)

  !! TODO_2 Run this block of code on a GPU

    do i = 1,N
      x(i)=sqrt(a*i*i)
    end do

  call check(x)

 contains
  subroutine fun(a,x)
    real    ::   a,x(*)
    integer ::   i
    do i = 1,N
      x(i)=sqrt(a*i*i)
    end do
  end subroutine

  subroutine check(x)
    real    ::     x(*)
    integer ::     i
    do i = 1,N
      if( abs(x(i)-sqrt(a*i*i)) > TOL ) then
        print*," Failed at ", i,x(i),sqrt(a*i*i)
        stop 1
      endif
    end do
    print*," PASSED"
  end subroutine

end program
