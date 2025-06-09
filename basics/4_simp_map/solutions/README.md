# persistent data with update.

Use the target data to create a data region,
and update a vector between offloads.

Instrument for offload, compile and run `data_region_update(.c|.F90):

1.) Look over the code.  
    Follow  TODO_1 and TODO_2 instructions (in comments).  

    For TODO_1 create a data region around the two offloads,
    so the p is mapped tofrom and v1 and v2 are mapped "to".
    Between the two offloads, new values for v1 are assigned.

    For TODO_2 update v1, after the new assignments, in the 
    target environment using the target update construct.

    Compile for offloading and run.

      $ nvc       -fopenmp -mp=gpu -O3 data_region_update.c 
      or
      $ nvfortran -fopenmp -mp=gpu -O3 data_region_update.F90
      $ ./a.out

    Now that you have it running, compare output with
    host execution.  What are two ways to do this?
    Hint: Compile it over with/without appropriate options, or
          tell the runtime not to offload with an environment variable.

    1 ---- recompile without OpenMP option.
    2 ---- disable offloading setting the OMP_TARGET_OFFLOAD env. var.

2.) If you printed the values of p immediately after the first
    offload, what would their values be?

    ---- the initialized values, the reference count prevents 
         implicit mapping.
