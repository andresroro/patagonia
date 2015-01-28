/**
 * \file  timing.c
 * \brief Timing routines
 */

#include "header.h"
#include <mpi.h>


/** \fn double get_time(void)
 * \brief Returns an elapsed time on the calling processor 
 * \return Time in seconds since an arbitrary time in the past.
 */

double get_time(void) {
	return MPI_Wtime();
}


