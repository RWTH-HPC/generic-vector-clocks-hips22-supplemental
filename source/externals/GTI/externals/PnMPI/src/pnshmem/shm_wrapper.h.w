/* This file is part of P^nMPI.
 *
 * Copyright (c)
 *  2008-2019 Lawrence Livermore National Laboratories, United States of America
 *  2011-2016 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
 *  2013-2019 RWTH Aachen University, Federal Republic of Germany
 *
 *
 * P^nMPI is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation version 2.1 dated February 1999.
 *
 * P^nMPI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with P^nMPI; if not, write to the
 *
 *   Free Software Foundation, Inc.
 *   51 Franklin St, Fifth Floor
 *   Boston, MA 02110, USA
 *
 *
 * Written by Martin Schulz, schulzm@llnl.gov.
 *
 * LLNL-CODE-402774
 */

#include <shmem.h>
#include <pshmem.h>

/*typedef int (*pnmpi_int_MPI_Pcontrol_t)(int level, ... );

void mpi_init_(int *ierr);
double mpi_wtick_(void);
double mpi_wtime_(void);*/

{{forallfn fn_name }}
{{ret_type}} {{sub {{fn_name}} '^sh' NQsh}}({{formals}});
{{endforallfn}}

#include <pnmpi/xmpi.h>

{{forallfn fn_name shmem_broadcast}}
#define {{fn_name}}_ID {{fn_num}}
{{endforallfn}}

{{forallfn fn_name shmem_broadcast}}
#define Internal_X{{fn_name}} {{sub {{fn_name}} '^sh' NQsh}}
{{endforallfn}}

{{forallfn fn_name MPI_Pcontrol shmem_broadcast}}
typedef {{ret_type}} (*pnshmem_int_{{fn_name}}_t)({{formals}});{{endforallfn}}

typedef struct pnshmem_functions_d
{
{{forallfn fn_name shmem_broadcast}}  pnshmem_int_{{fn_name}}_t *pnshmem_int_{{fn_name}};
{{endforallfn}}
} pnshmem_functions_t;

#define SHM_INITIALIZE_ALL_FUNCTION_STACKS(mods) \
{{forallfn fn_name shmem_broadcast}}SHM_INITIALIZE_FUNCTION_STACK("{{fn_name}}", {{fn_name}}_ID, pnshmem_int_{{fn_name}}_t, pnshmem_int_{{fn_name}}, mods, {{fn_name}});\
{{endforallfn}}
