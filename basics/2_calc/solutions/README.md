# Offloading Square root calculation as a function and as a block of code.

On TACC systems, access a gpu node by simply executing the idev command.

Learn the importance of using the -O3 option in offloading.
Offload square root calculations, `sqrt(.c|.F90)`.

1.) Look over the code.
    What is the basic mathematical operation in function fun() 
    and the code block?
    ____  sqrt

    Is there a separate logical unit in the SM for square root?
    ____ yes in a Special Function Units (SFU)


2.) Insert OpenMP directives as described by TODO1 and TODO2 code comments.
    Note: this code only executes on a single thread.

        $ nvc       -fopenmp -mp=gpu sqrt.c   -lm -O3
        $ nvfortran -fopenmp -mp=gpu sqrt.F90 -lm -O3

    Time the execution with the shell built-in timer command:

          time ./a.out

    Now, create a non-optimized executable, and time it:

        $ nvc       -fopenmp -mp=gpu sqrt.c   -lm 
        $ nvfortran -fopenmp -mp=gpu sqrt.F90 -lm 

        $ time ./a.out    # You can abort if you get impatient.

    Time the execution with the shell built-in timer command:

          time ./a.out

    Was there a difference in performance with the NVIDIA compiler?
     
     
    time -O3  ---- ~ 0.050s c-code   ~0.096s   !0.025  F90-code
    time nopt ---- ~ 0.075s c-code   ~0.025s  F90-code
    --- Compiler optimization (-O3) can make a difference, particularly
        when the GCC compilers are used.

3.) Compare the time for the gcc compiler WITH and WITHOUT the -O3 option.

    First, load up GCC:

        $ ml gcc

        $ gcc      -fopenmp -foffload=nvptx-none sqrt.c   -lm -O3
        $ gfortran -fopenmp -foffload=nvptx-none sqrt.F90 -lm -O3

        $ time ./a.out

        $ gcc      -fopenmp -foffload=nvptx-none sqrt.c   -lm
        $ gfortran -fopenmp -foffload=nvptx-none sqrt.F90 -lm

    How much fast is the -O3 code than non-optimized code?
         
    C code and Fortran code
    time -O3  ----   0.050s
    time nopt ----   0.150s  #this us to be 40x slower

    **** change back to nvidia compilers:

        $ ml nvidia
