#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include "createoutputfile.h"
#include "printlines.h"
#include "splitsearch.h"
#include "argparsing.h"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char * argv[]) {

  // Some costants
  const int PID = getpid();
  const int MAX_CHILDREN = 10000;

  // Some variables
  int * r = malloc(sizeof(int));  // Max number of result
  int max = 0;                    // Total lines of the input file
  int line = 0;                   // Line where I found the value
  int * arg = NULL;               // Parsed command line arguments
  int pfd[2];                     // Pipe where we save the r value
  int FIFO, FIFOread, FIFOwrite;  // FIFO file descriptor
  FILE * out = NULL;              // Output file

  // Check if the user supplied enough
  // flags to run the script.
  arg = argParser(argc, argv);

  // Check whether output file is specified
  if (arg[2] != -1) {
    out = createoutputfile(argv[arg[2]]);
    if (out == NULL) {
      perror("Output file: ");
      exit(1);
    }
  }

  // Create R fifo
  if (pipe(pfd) == -1) {
    perror("Pipe error: ");
    exit(1);
  };

  // Read the entire file to estimate
  // its number of lines (it exit if the file
  // doesn't exist,)
  int file = open(argv[arg[1]], O_RDONLY);
  if (file == -1) {
    perror(argv[arg[1]]);
    exit(1);
  }
  max = length(file);
  close(file);

  // Generate FIFO
  FIFO = mkfifo("FIFO", FILE_MODE);
  FIFOread = open("FIFO", O_RDONLY | O_NONBLOCK);
  FIFOwrite = open("FIFO",O_WRONLY | O_NONBLOCK);

  // Check whether the user has specified a maximum
  // number of output.
  if (arg[3] == -1) {
    *r = max;
  } else {
    *r = atoi(argv[arg[3]]);
  }
  write(pfd[1],r,sizeof(int));

  // Set the max number of process for this execution
  struct rlimit limits;
  getrlimit (RLIMIT_NPROC, &limits);
  limits.rlim_cur = MAX_CHILDREN;
  setrlimit(RLIMIT_NPROC, &limits);

  // Perform a search for the specific value
  line = search(argv[arg[1]], 0, max, argv[arg[0]], pfd);

  // If we have found the value, print it inside FIFO
  if (line > 0) {
    write(FIFOwrite, &line, sizeof(int));
  }

  // If it is the father process, then print all the pipe
  if (PID == getpid()) {
    int * buffer = malloc(sizeof(int));
    while (read(FIFOread, buffer, sizeof(int)) > 0) {
      printlines(buffer, out);
    }
    unlink("FIFO");
  }

  // Free some variables
  free(r);

  if (line > 0) return 0;
  return 1;
}
