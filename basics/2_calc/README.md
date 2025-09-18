# Offloading square root calculation as a function and as a block of code.

On TACC systems, access a gpu node by simply executing the idev command.

Learn the importance of using the -O3 option in offloading.
Offload square root calculations, `sqrt(.c|.F90)`.

1.) Look over the code.
    What is the basic mathematical operation in function fun() 
    and the code block?
    ____

    Is there a separate logical unit in the SM for square root?
    ____

    So, floating point units perform the square root operations.

2.) Insert OpenMP directives as described by TODO_1 and TODO_2,
    to execute the code on the GPU.

        $ nvc       -fopenmp -mp=gpu sqrt.c   -lm -O3
        $ nvfortran -fopenmp -mp=gpu sqrt.F90 -lm -O3

    Time the execution with the built-in timer command:

          time ./a.out

    Now, create a non-optimized executable, and time it:

        $ nvc       -fopenmp -mp=gpu sqrt.c   -lm 
        $ nvfortran -fopenmp -mp=gpu sqrt.F90 -lm 

    Time the execution with the built-in timer command:

          time ./a.out

    Was there a difference in performance with the NVIDIA compiler?
     
     
    time -O3  ----
    time nopt ----

3.) Compare the time for the gcc compiler WITH and WITHOUT the -O3 option.

    First, load up GCC:

        $ ml gcc

        $ gcc      -fopenmp -foffload=nvptx-none sqrt.c   -lm -O3
        $ gfortran -fopenmp -foffload=nvptx-none sqrt.F90 -lm -O3

        $ time ./a.out

        $ gcc      -fopenmp -foffload=nvptx-none sqrt.c   -lm
        $ gfortran -fopenmp -foffload=nvptx-none sqrt.F90 -lm

        $ time ./a.out    # You can abort if you get impatient.

    How much fast is the -O3 code than non-optimized code?
         
    time -O3  ----
    time nopt ----

    **** change back to nvidia compilers:

        $ ml nvidia
 =================================================================
