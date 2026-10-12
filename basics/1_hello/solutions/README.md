# Hello world with OpenMP offloading

On TACC systems, access a gpu node by simply executing the idev command.

Compile and run the simple OpenMP `hello(.c|.F90)` with/without offloading.

1.) Look over the code.
    What is the purpose of omp_get_num_devices()?
    What is the purpose of omp_is_init_device()?
    
    _____ get the number of offload devices
    _____ return (1 C/C++) (.T. fortran) if run on HOST

2.) Compile the code, AS IS, without any openmp support.

        $ nvc hello.c  |  nvfortran hello.F90

    What is the problem?
    Hint:  OMP functions need prototypes.

    ---  needs omp.h header (C/C++), use omp_lib (Fortran)

 TODO1:
    Allow openmp functions support by
    inserting header (for C/C++) or use statement (for F90).
    Compile with JUST openmp compiler support (-fopenmp) and run.
                   
        $ nvc -fopenmp hello.c | nvfortran -fopenmp hello.F90

    Where did the code run? ____ HOST

3.)
 TODO2:
    Insert OpenMP directives as described by TODO2 code comments.
    to execute omp_is_init_device() on the device.
    Compile with only the -fopenmp option.

    Where did the code run? ____ HOST

    On HPC systems it runs on the host, as a fallback, 
    since no compiler offloading support is specified.

4.) Compile code with openmp offloading support and run.

        $  nvc       -fopenmp -mp=gpu hello.c
        $  nvfortran -fopenmp -mp=gpu hello.F90

    Where did the binary run? ____ GPU
                            
5.) Now turn off offloading with the OMP_TARGET_OFFLOAD variable.

        $  export OMP_TARGET_OFFLOAD=disabled
        $  ./a.out

    Where did it run?  ____ HOST

  EXTRA
    ON A LOGIN node (without OMP_TARGET_OFFLOAD set)
    execute:
        $ ./a.out

    Where did it run?  ____ HOST !

    Now, set offloading to mandatory and run:

        $  export OMP_TARGET_OFFLOAD=mandatory
        $  ./a.out

    What happened? 

      ---- Code Aborted as required for mandatory
