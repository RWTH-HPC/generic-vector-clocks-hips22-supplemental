# This file is part of P^nMPI.
#
# Copyright (c)
#  2008-2019 Lawrence Livermore National Laboratories, United States of America
#  2011-2016 ZIH, Technische Universitaet Dresden, Federal Republic of Germany
#  2013-2019 RWTH Aachen University, Federal Republic of Germany
#
#
# P^nMPI is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License as published by the Free
# Software Foundation version 2.1 dated February 1999.
#
# P^nMPI is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with P^nMPI; if not, write to the
#
#   Free Software Foundation, Inc.
#   51 Franklin St, Fifth Floor
#   Boston, MA 02110, USA
#
#
# Written by Martin Schulz, schulzm@llnl.gov.
#
# LLNL-CODE-402774

include(PnMPI_headers)


# Include common include directories.
#
# As almost all source code files need any kind of PnMPI header to be included,
# the common PnMPI header path will be included for all subdirectories instead
# of including the path independently in all paths.
include_directories(${PNMPI_HEADER_DIR})


add_subdirectory(modules)
add_subdirectory(patch)
add_subdirectory(pnmpi)
add_subdirectory(pnmpize)
if (ENABLE_OPENSHMEM)
  add_subdirectory(pnshmem)
  add_subdirectory(pnshmemze)
endif()
