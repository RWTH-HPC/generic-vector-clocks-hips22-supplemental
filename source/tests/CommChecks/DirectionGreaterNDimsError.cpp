/* Part of the MUST Project, under BSD-3-Clause License
 * See https://hpc.rwth-aachen.de/must/LICENSE for license information.
 * SPDX-License-Identifier: BSD-3-Clause
 */

// UNSUPPORTED: fast-tests
// RUN: %must-run %mpiexec-numproc-flag 2 \
// RUN: %must-bin-dir/DirectionGreaterNDimsError 2>&1 \
// RUN: | %filecheck %s

// CHECK: [MUST-REPORT]{{.*Error:.*Argument.*[(]direction[)].*topology, but is out of range, a number from 0 to ndims-1 was expected}}

/**
 * @file DirectionGreaterNDimsError.cpp
 * This is a a test for the analysis group CommChecks.
 *
 * Description:
 * Creates a cartesian communicator and do a shift on this communicator
 * with using a direction that is greater then the number of dimensions in the
 * communicator. This will cause an error.
 *
 *  @date 29.04.2011
 *  @author Mathias Korepkat
 */

#include <iostream>
#include <mpi.h>

int main (int argc, char** argv)
{
	int size, rank;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	MPI_Status status;

	//Enough tasks ?
	if (size < 2)
	{
		std::cerr << "This test needs at least 2 processes!"<< std::endl;
		MPI_Finalize();
		return 1;
	}

	//Say hello
	std::cout << "Hello, I am rank " << rank << " of " << size << " processes." << std::endl;

	//create a cartesian communicator
	MPI_Comm comm;
	int dims[2], periods[2];
	int source, dest;
	dims[0] = 2;
	dims[1] = 1;
	periods[0] = 1;
	periods[1] = 1;

	MPI_Cart_create( MPI_COMM_WORLD, 2, dims, periods, 0, &comm );
	MPI_Cart_shift(comm, 3, 1,&source,&dest);
	if(comm != MPI_COMM_NULL)
		MPI_Comm_free( &comm );

	//Say bye bye
	std::cout << "Signing off, rank " << rank << "." << std::endl;

	MPI_Finalize ();

	return 0;
}
