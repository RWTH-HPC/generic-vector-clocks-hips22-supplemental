// REQUIRES: tsan

// RUN: rm -f %t/MUST_Output.html

// RUN: %mustrun-tsan %mpiexec-numproc-flag 2 \
// RUN: --must:output-dir %t --must:output html \
// RUN: %must-bin-dir/MpiTSanIsend 2>&1  || true

// RUN: cat %t/MUST_Output.html | %filecheck %check-prefixes %s

// CHECK: {{.*Data race.*MPI_Isend}}

#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <omp.h>

#define NUM_THREADS 2

int main(int argc, char* argv[])
{
  int provided;
  int rdata[NUM_THREADS], sdata[NUM_THREADS], rank, size;
  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
  if(provided < MPI_THREAD_FUNNELED)
  {
    printf("MPI level insufficient\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Request req;
  MPI_Irecv(rdata, NUM_THREADS, MPI_INT, size-rank-1, 42, MPI_COMM_WORLD, &req);
#pragma omp parallel num_threads(NUM_THREADS)
{
  // CHECK-ST-DAG: isend.c:[[@LINE+1]]
    sdata[omp_get_thread_num()] = omp_get_thread_num();
#pragma omp master
  {
    MPI_Request req2;
    // CHECK-ST-DAG: isend.c:[[@LINE+1]]
    MPI_Isend(sdata, NUM_THREADS, MPI_INT, size-rank-1, 42, MPI_COMM_WORLD, &req2);
    MPI_Wait(&req2, MPI_STATUS_IGNORE);
  }
}
  MPI_Wait(&req, MPI_STATUS_IGNORE);
  MPI_Finalize();
  return EXIT_SUCCESS;
}
