#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include "printlines.h"
#include "splitsearch.h"
#include "argparsing.h"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char * argv[]) {

  /**** BEGIN CONTROL AND SET SECTION ****/

  /* Some costants */
  const int PID = getpid();
  const int MAX_CHILDREN = 10000;

  /* Some variables */
  int * r = malloc(sizeof(int));  // Max number of result
  int max = 0;                    // Total lines of the input file
  int * line = NULL;              // Lines where I found the value
  int * arg = NULL;               // Parsed command line arguments
  int pfd[2];                     // Pipe where we save the r value
  int FIFO, FIFOread, FIFOwrite;  // FIFO file descriptor
  FILE * out = NULL;              // Output file

  /*
    Check if the user supplied enough
    flags to run the script.
  */
  arg = argParser(argc, argv);

  /* Check whether output file is specified */
  if (arg[2] != -1) {
    out = fopen(argv[arg[2]],"w");
    if (out == NULL) {
      perror("Output file: ");
      exit(1);
    }
  }

  /* Create pipe to store the max number of result */
  if (pipe(pfd) == -1) {
    perror("Pipe error: ");
    exit(1);
  };

  /*
    Read the entire file to estimate
    its number of lines (it exit if the file
    doesn't exist,)
  */
  int file = open(argv[arg[1]], O_RDONLY);
  if (file == -1) {
    perror(argv[arg[1]]);
    exit(1);
  }
  max = length(file);
  close(file);

  /* Generate FIFO to store results */
  FIFO = mkfifo("FIFO", FILE_MODE);
  FIFOread = open("FIFO", O_RDONLY | O_NONBLOCK);
  FIFOwrite = open("FIFO",O_WRONLY | O_NONBLOCK);

  /*
    Check whether the user has specified a maximum
    number of output.
  */
  if (arg[3] == -1) {
    *r = max;
  } else {
    *r = atoi(argv[arg[3]]);
  }
  write(pfd[1],r,sizeof(int));

  /* Set the max number of process for this execution */
  struct rlimit limits;
  getrlimit (RLIMIT_NPROC, &limits);
  limits.rlim_cur = MAX_CHILDREN;
  setrlimit(RLIMIT_NPROC, &limits);

  /**** END ****/

  /**** BEGIN SEARCH SECTION ****/

  /* Print some informations */
  printf("[*] Splitsearch version 0.1\n");
  printf("[*] Filename: %s\n", argv[arg[1]]);
  printf("[*] Number of lines: %i\n", max);
  printf("[*] Begin search of value %s:\n", argv[arg[0]]);

  /*
    Perform a search for the specific value and
    set the exit_value for this process
  */
  line = search(argv[arg[1]], 1, max, argv[arg[0]], pfd);

  /* If we have found the value, write it inside FIFO */
  if (*line > 0) {
    int i = 0;
    while(line[i]) {
      write(FIFOwrite, &line[i], sizeof(int));
      i++;
    }
  }

  /* If it is the father process, then print all the FIFO */
  if (PID == getpid()) {
    int * buffer = malloc(sizeof(int));
    int found = 0;
    printf("\n[*] Search ended.\n[*] Value found in line\\s:\n");
    while (read(FIFOread, buffer, sizeof(int)) > 0) {
      printlines(buffer, out);
      found = 1;
    }
    if (found == 0) {
      printf("0 - Not found\n");
    }
    unlink("FIFO");
  } else {
    printf("=");
  }

  /**** END SEARCH SECTION ***/

  /* Free some variables previously allocated */
  free(r);
  free(line);
  return 0;
}
