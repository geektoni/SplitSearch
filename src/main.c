#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "splitsearch.h"
#include "argparsing.h"

int main(int argc, char * argv[]) {

  // Check if the user supplied enough
  // flags to run the script.
  int * arg = argParser(argc, argv);

  // Read the entire file to estimate
  // its number of lines
  int file = open(argv[arg[1]], O_RDONLY);
  int max = length(file);
  close(file);

  // Perform a search for the specific value
  search(argv[arg[1]], 0, max, argv[arg[0]]);

  // This line will block this main process
  // until no child is left alive. This is made
  // to avoid strange output situation inside
  // bash screen.
  while (wait(NULL)) {
    if (errno == ECHILD) {
      break;
    }
  }

  return 0;
}
