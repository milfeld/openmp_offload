# Distributing worksharing loops across teams

On TACC systems, access a gpu node by simply executing the idev command.

Learn how to distribute worksharing loops across teams.
Offload axpy loop, `axpy(.c|.F90)`.

1.) TARGET TEAMS DISTRIBUTE PARALLEL FOR
    Look over the code.
    It times the axpy on the host, and on the gpu.

    TODO_1-3
    Workshare the host loops with parallel for; the axpy loop is timed.
    Insert target teams distribute parallel for as described in TODO_1
    
    Capture the performance for these compilers: nvidia and gcc

      $  ml nvidia
    
      $  nvc       -fopenmp -mp=gpu axpy.c   -lm -O3
      OR
      $  nvfortran -fopenmp -mp=gpu axpy.F90 -lm -O3
    
      $ export OMP_NUM_THREADS=72 (for host axpy)
      $  ./a.out   #record the GPU time below
    
      $ ml gcc
    
      $ gcc       -fopenmp -foffload=nvptx-none  axpy.c   -lm -O3
      OR
      $ gfortran  -fopenmp -foffload=nvptx-none  axpy.F90 -lm -O3
    
      $ export OMP_NUM_THREADS=72 (for host axpy)
      $ ./a.out   #record the GPU time below

           Compiler  HOST     GPU
      ---- NVIDIA    ...      ...
      ---- GCC       ...      ...
      ---- LLVM      0.0155  0.0063 

      Note:  if you recompile with target teams distribute parallel for simd
             You will get the same times, except GCC offload improves by 5 x:
      ---- GCC-simd  0.0042  0.0045
      
      Which compiler does the best with host and gpu performance? 

  ***** Change back to using the nvidia compiler  ******

      $ ml nvidia

2.) TARGET TEAMS LOOP
    TODO_4
    Replace the target teams distribute parallel for construct with
                target teams loop                as described in TODO_3

    Repeat the module loading, compiling and execution in 1.)

    Report the timings:
         compiler    target teams              target teams  TTDPF simd
                     distribute parallel for   loop
                     performance (sec)                        FYI (approx)
         gcc         0.01987                    0.0....      0.00440
         nvidi       0.00175                    0.0....      0.00173
         llvm        0.00065                    0.0....      0.00065
    
3.) Run any compiled version with OMP_NUM_THREADS=1.
    How much slower is the HOST execution with 1 thread, compared to 72?
    ---- 


4.) Try running any of your executables on the login
    (Don't forget to have the appropriate compiler loaded.)

    $login  ./a.out
    Do the host (single thread) and gpu fallback (onto host) perform the same?
    ----


     $login export OMP_TARGET_OFFLOAD=MANDATORY
     $login ./a.out

    What happened.

    Response:
    ----

5.) TODO_5
    Change the code to back to use "target teams distribute parallel for",
    and use 1024 and 512 teams with the num_teams(##) clause.

      $  #use num_teams(...) on target teams distribute parallel for
      $  ml nvidia
    
      $  nvc       -fopenmp -mp=gpu axpy.c   -lm -O3
      OR
      $  nvfortran -fopenmp -mp=gpu axpy.F90 -lm -O3
    
      $  ./a.out   

    Which number is optimal, 512, or 1024?
      ---- 
 =================================================================
