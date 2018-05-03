//
// Starting code for the MPI coursework.
//
// Compile with:
//
// mpicc -Wall -o cwk1 cwk1.c
//
// or use the provided makefile.
//

//
// Includes
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// Some extra routines for this coursework. DO NOT MODIFY OR REPLACE THESE
// ROUTINES, as this file will be replaced with a different version for
// assessment.
#include "cwk2_extras.h"

//
// Main
//
int main(int argc, char **argv) {
  int i;

  // Initialise MPI and get the rank and no. of processes.
  int rank, numProcs;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf("Rank - %i Processes - %i\n", rank, numProcs);

  int *localData = (int *)malloc(sizeof(int) * 2);
  int *data;
  // Read in the image file to rank 0.
  int *image = NULL, maxValue, pixelsPerProc, dataSize;
  if (rank == 0) {
    // Read in the file and extract the maximum grey scale value and the data
    // size (including padding bytes). Defined in cwk2_extras.h; do not change,
    // although feel free to inspect.
    image = readImage("image.pgm", &maxValue, &dataSize, numProcs);
    if (image == NULL) {
      MPI_Finalize();
      return EXIT_FAILURE;
    }

    // The image size has already been rounded up to a multiple of numProcs by
    // "readImage()".
    pixelsPerProc = dataSize / numProcs;

    printf(
        "Rank 0: Read in PGM image array of size %d (%d per process), with max "
        "value %d.\n",
        dataSize, pixelsPerProc, maxValue);

    // send the size of the data and the maxValue to all processes
    // we use and array to limit the number of braodcasts to one
    localData[0] = pixelsPerProc;
    localData[1] = maxValue;
    MPI_Bcast(localData, 2, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    // get the size of the local data that we will recieve
    MPI_Bcast(localData, 2, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Data size - %d, max value - %d\n", localData[0], localData[1]);

    // update local variables
    pixelsPerProc = localData[0];
    maxValue = localData[1];

    // allocate memory for the data
    // we do it here to avoid allocating it in rank 0 as it has access to the
    // global data
    data = (int *)malloc(sizeof(int) * pixelsPerProc);
  }

  // Allocate memory for the final histogram on rank 0.
  int *combinedHist = NULL;
  if (rank == 0) {
    combinedHist = (int *)malloc((maxValue + 1) * sizeof(int));
    if (!combinedHist) return allocateFail("global histogram", rank);

    for (i = 0; i < maxValue + 1; i++) combinedHist[i] = 0;
  }

  //
  // Your parallel code goes here. Feel free to change anything else in this
  // file, EXCEPT calls to the routines in cwk2_extras.h which MUST be called as
  // provided.
  //

  // on rank 0 we split and send the data to all processes
  // all other ranks read the recieved data into the data variable
  if (rank == 0) {
    for (i = 1; i < numProcs; i++) {
      printf("Send to - %d\n", i);
      MPI_Send(&image[pixelsPerProc * (i - 1)], pixelsPerProc, MPI_INT, i, 0,
               MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(data, pixelsPerProc, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }

  // Allocate memory for the check histogram, and then initialise it to zero.
  int *checkHist = (int *)malloc((maxValue + 1) * sizeof(int));
  if (!checkHist) return allocateFail("histogram for checking", rank);
  for (i = 0; i < maxValue + 1; i++) checkHist[i] = 0;

  // do the work of couting the numbers
  // rank 0  is special because he uses the whole data set
  // all other ranks use the data variable
  if (rank == 0) {
    // we update the combinedHist as all the data will eventually end in it
    for (i = pixelsPerProc * (numProcs - 1); i < dataSize; i++) {
      if (image[i] >= 0) {
        combinedHist[image[i]]++;
      }
    }
  } else {
    for (i = 0; i < pixelsPerProc; i++) {
      if (data[i] >= 0) {
        checkHist[data[i]]++;
      }
    }
  }
free(data);
  // POINT TO POINT COMMUNICATION CODE
  // combine the results in rank 0
  // if (rank == 0) {
  //   int *temp = (int *)malloc((maxValue + 1) * sizeof(int));
  //   for (i = 0; i < maxValue + 1; i++) temp[i] = 0;

  //   // rank 0 will recieve data from all other processes so we recieve using
  //   // numprocs - 1
  //   for (i = 0; i < numProcs - 1; i++) {
  //     printf("Call to combine - %d\n", i);
  //     // we use MPI_ANY_SOURCE because order does not matter
  //     MPI_Recv(temp, maxValue, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
  //              MPI_STATUS_IGNORE);

  //     int j;
  //     for (j = 0; j <= maxValue; j++) {
  //       combinedHist[j] += temp[j];
  //     }
  //   }

  //   free(temp);
  // } else {
  //   // all other processes eend to rank 0 the data
  //   MPI_Send(checkHist, maxValue, MPI_INT, 0, 0, MPI_COMM_WORLD);
  // }

  // combine data using a binary tree
  // temp is used to recieve the data from other processes when combinibng the
  // data using a tree
  int *temp = (int *)malloc((maxValue + 1) * sizeof(int));
  for (i = 0; i < maxValue + 1; i++) temp[i] = 0;

  // each iteration we need only half of the processes because the second half
  // data has already been combined. This makes this algorithim wun in O(logn).
  // we check if the proccess has a rank of < i to make sure we don't combine
  // the same data twice.
  for (i = numProcs; i >= 1; i = i / 2) {
    if (rank < i) {
      if (rank >= i / 2) {
        // the second half of the processes needs to send the data to the first
        // half
        if (rank != rank - (i / 2)) {
          printf("Process - %d sending data to process - %d\n", rank,
                 rank - (i / 2));
          MPI_Send(checkHist, maxValue, MPI_INT, rank - (i / 2), 0,
                   MPI_COMM_WORLD);
        }
      } else if (rank < i / 2) {
        // the first half of the processes recieve data from the second half and
        // combine it
        printf("Process - %d recieving data from process - %d\n", rank,
               rank + (i / 2));

        //  we could have used MPI_ANY_SOURCE to read the data but since we can
        //  calculate it
        // I am using a specific procces to recieve from.
        // Lets just hope I always send from that proccess as well.
        MPI_Recv(temp, maxValue, MPI_INT, rank + (i / 2), 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        int j;
        if (rank == 0) {
          // Special case for rank 0 as it uses the combined histogram direcly
          printf("Process - %d combining data\n", rank);
          for (j = 0; j <= maxValue; j++) {
            combinedHist[j] += temp[j];
          }
        } else {
          printf("Process - %d combining data\n", rank);
          for (j = 0; j <= maxValue; j++) {
            checkHist[j] += temp[j];
          }
        }
      }
    }
  }

  free(temp);

  // if (rank == 0) {
  //   for (i = 0; i <= maxValue; i++) {
  //     combinedHist[i] = checkHist[i];
  //   }
  // }

  free(checkHist);

  // for (i = 0; i < maxValue; i++) {
  //   printf("Greyscale value %i:\tCount %i\t\n", i, checkHist[i]);
  // }

  //
  // Constructs the histogram in serial on rank 0. Can be used as part of a
  // check that your parallel version works.
  //
  // if (rank == 0) {
  //   // Allocate memory for the check histogram, and then initialise it to
  //   zero. int *checkHist = (int *)malloc((maxValue + 1) * sizeof(int)); if
  //   (!checkHist) return allocateFail("histogram for checking", rank); for (i
  //   = 0; i < maxValue + 1; i++) checkHist[i] = 0;

  //   // Construct the histogram using the global data only.
  //   for (i = 0; i < dataSize; i++) {
  //     if (image[i] >= 0) {
  //       checkHist[image[i]]++;
  //     }
  //   }

  //   for (i = 0; i <= maxValue; i++) {
  //     combinedHist[i] = checkHist[i];
  //   }

  //   // Display the histgram.
  //   // for (i = 0; i < maxValue + 1; i++) {
  //   //   printf("Greyscale value %i:\tCount %i\t(check: %i)\n", i,
  //   //   combinedHist[i],
  //   //          checkHist[i]);
  //   // }

  //   free(checkHist);
  // }

  //
  // Clear up and quit.
  //
  if (rank == 0) {
    saveHist(combinedHist, maxValue);  // Defined in cwk2_extras.h; do not
                                       // change or replace the call.
    free(image);
    free(combinedHist);
  }

  MPI_Finalize();
  return EXIT_SUCCESS;
}