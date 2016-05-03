#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "splitsearch.h"
#include "argparsing.h"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char * argv[]) {

  // Some costants
  const int PID = getpid();
  const int MAX_CHILDREN = 10000;

  // Check if the user supplied enough
  // flags to run the script.
  int * arg = argParser(argc, argv);

  // Generate FIFO
  int FIFO = mkfifo("FIFO", FILE_MODE);
  int FIFOread = open("FIFO", O_RDONLY | O_NONBLOCK);
  int FIFOwrite = open("FIFO",O_WRONLY | O_NONBLOCK);

  // Read the entire file to estimate
  // its number of lines (it exit if the file
  // doesn't exist,)
  int file = open(argv[arg[1]], O_RDONLY);
  if (file == -1) {
    perror(argv[arg[1]]);
    exit(-1);
  }
  int max = length(file);
  close(file);

  // Set the max number of process for this execution
  struct rlimit limits;
  getrlimit (RLIMIT_NPROC, &limits);
  limits.rlim_cur = MAX_CHILDREN;
  setrlimit(RLIMIT_NPROC, &limits);

  // Perform a search for the specific value
  int line = search(argv[arg[1]], 0, max, argv[arg[0]]);

  // This line will block this main process
  // until no child is left alive. This is made
  // to avoid strange output situation inside
  // bash screen.
  while (wait(NULL) > 0);

  // If we have found the value, print it inside FIFO
  if (line > -1) {
    write(FIFOwrite, &line, sizeof(int));
  }

  // If it is the father process, then print all the pipe
  if (PID == getpid()) {
    int * buffer = malloc(sizeof(int));
    while (read(FIFOread, buffer, sizeof(int)) > 0) {
      printf("%i\n", *buffer+1);
    }
    unlink("FIFO");
  }

  return 0;
}
