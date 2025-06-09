# Asynchronous Offloading

The code loops over partitions (sections) of
an AXPY loop.

The purpose of this example is to illustrate
the execution of simultaneous offloads
(of the AXPY sections) to multiple GPUs.
(Most systems have have more than 1 GPU/node.)

Vista only has 1 GPU. Nevertheless, the
code was designed to work even for a single GPU.

Regardless, it is instructive to instrument the
code with OpenMP constructs to offload the
sections asynchronously (with a nowait clause
and a taskwait contruct).

For Vista, we show how to modify the program (in 2.)
to offload multiple sections to the single Hooper GPU.
 
1.) Look over the axpy.c/F90 code.  
    The code calls omp_get_num_devices() to obtain the number of gpus (ndev),
    and divides N (number of elments in a AXPY algorithm) for
    partitioning the sections (N/ndev iterations) among the GPUs.

    Set up asynchronous execution following
    TODO_1, TODO_2, and TODO_3 instructions (in the comments).  

    Compile and execute.

      $ nvc       -fopenmp -mp=gpu -O3 async.c 
      or
      $ nvfortran -fopenmp -mp=gpu -O3 async.F90
      $ ./a.out

2.)  Look over the tasks.c/F90 code. 
     You can always just queue up a "bunch of tasks"
     to run on a single GPU.  We will do this for
     Vista (which only has one GPU) with the code
     you modified above.

     USE tasks.c/F90.

     TODO_1  Hard set ndev to a small integer (e.g. 3)
     TODO_2  Remove the parallel and master constructs.
     TODO_3  Change device(id) to device(0) so that only
             the single Vista GPU (id=0) is used.

     TODO 4  Wait for the task to finish with the taskwait construct.

     Compile and run:
      $  nvc       -fopenmp -mp=gpu -O3 tasks.c 
      or
      $  nvfortran -fopenmp -mp=gpu -O3 tasks.F90
      $  ./a.out

      What could happen without the taskwait construct?
     ---- The printed values may be the initial values,
          because the tasks may not have run yet.

      Why is it safe to use ib and ie in the code block
      which is run later as a "target task".  
      (i.e. if tasks don't start executing until all are 
            generated, would you expect them all to
            just use the final ib and ie?)
     ---- Yes it is safe, for the target construct ib and ie
          are scalars, and are therefore firstprivate. (A
          private copy of the variables and thier values 
          are created for each target task).

=================================================================

Other Information:  how to run multiple processes simultaneously
                    with MPS
     Using MPS has shown to be effective in running
     multiple executables (such as amber) simultaneously.

      $  export CUDA_MPS_PIPE_DIRECTORY=`pwd`/MPS_log
      $  export CUDA_MPS_LOG_DIRECTORY=`pwd`/MPS_log
      $  export CUDA_VISIBLE_DEVICES=0
      $  export CUDA_DEVICE_MAX_CONNECTIONS=3
      $  nvidia-cuda-mps-control -d

      $  ./a.out &
      $  ./a.out &
      $  wait
