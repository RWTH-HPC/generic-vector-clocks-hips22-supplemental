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

include(PnMPI_doc)


# Add C11 flags, if C11 is available.
if (C11_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C11_FLAGS}")
endif ()

# Check if atomics are available for thread safe storage. First we try to use
# C11 atomics, next the GCC builtin atomic_fetch_add method and finally
# sync_fetch_and_add.
if (NOT C11_ATOMICS_FOUND)
  find_package(BuiltinAtomic)
  if (NOT BUILTINATOMIC_FOUND)
    find_package(BuiltinSync)
  endif ()
endif ()

configure_file(config.h.in config.h)


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR} # Required for generated source files.
  ${CMAKE_CURRENT_BINARY_DIR}
)


#
# Add the counter module
#
add_shm_wrapped_file(counter.c counter.c.w -w)
pnmpi_add_xmpi_module(shm-metrics-counter "${CMAKE_CURRENT_BINARY_DIR}/counter.c")

pnmpi_add_module_man(shm-metrics-counter module_metrics_counter)

install(TARGETS shm-metrics-counter DESTINATION ${PnMPI_MODULES_DIR})