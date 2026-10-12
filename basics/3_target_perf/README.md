# Distributing worksharing loops across teams

On TACC systems, access a gpu node by simply executing the idev command.

Learn how to distribute worksharing loops across teams.
Offload axpy loop, `axpy(.c|.F90)`.
Look over the saxpy loops.


1-
2.) TODO_1-2
    Insert PARALLEL FOR construct before host loops
    (There is a timer around the axpy on the host.)

3-
5.) TODO_3-5
    Offload device loop different ways. 
    (There is a timer around the axpy for the device.)
    (Note that the data movement is not in the timer--
     a target data construct outside the time wrapper

3.) TODO_3
    TARGET TEAMS DISTRIBUTE PARALLEL FOR

    Insert target teams distribute parallel for as described in TODO_3
    
    Capture the performance for these compilers: nvidia and gcc

      $  export OMP_NUM_THREADS=36 (for host axpy, perforance peaks 16 ... 72)
      $  ml nvidia
    
      $  nvc       -fopenmp -mp=gpu axpy.c   -lm -O3
      OR
      $  nvfortran -fopenmp -mp=gpu axpy.F90 -lm -O3
    
      $  ./a.out   #record the GPU time below
    
      $ ml gcc
    
      $ gcc       -fopenmp -foffload=nvptx-none  axpy.c   -lm -O3
      OR
      $ gfortran  -fopenmp -foffload=nvptx-none  axpy.F90 -lm -O3
    
      $ export OMP_NUM_THREADS=32 (for host axpy)
      $ ./a.out   #record the GPU time below

           Compiler  HOST     GPU
      ---- NVIDIA    ...      ...
      ---- GCC       ...      ...
      ---- LLVM      0.0155  0.0063 

      Note:  if you recompile with target teams distribute parallel for simd
             You will get the same times, except GCC offload improves by 5 x:
      ---- GCC-simd  0.0043  0.0045
      
      Which compiler does the best with host and gpu performance? 

  ***** Change back to using the nvidia compiler  ******

      $ ml nvidia

4.) TODO_4
    Replace the target teams distribute parallel for construct with
                target teams loop                as described in TODO_3

    Repeat the module loading, compiling and execution in above 

    Report the timings:
         compiler    TTDPF                    TTDPF simd     target teams loop 
                     target teams distribute                 teams loop
                     parallel for (TTDPF)     FYI (approx)   0.....
         gcc         0.01987                  0.00440        0.....
         nvidia      0.00175                  0.00173        0.....
         llvm        0.00065                  0.00065        0.....
    
4a) Run any compiled version with OMP_NUM_THREADS=1.
    How much slower is the HOST execution with 1 thread, compared to 72?
    ---- 


4b) Try running any of your executables on the login
    (Don't forget to have the appropriate compiler loaded.)

    $login  ./a.out
    Is the host (single thread) and gpu fallback (onto host) performance the same?
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
