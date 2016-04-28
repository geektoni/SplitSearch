#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "splitsearch.h"

int main(int argc, char * argv[]) {

  int file = open(argv[1], O_RDONLY);
  int max = length(file);
  close(file);

  // Perform a search for the specific value
  search(argv[1], 0, max, argv[2]);

  // This line will block this main process
  // untill no child is left alive. This is made
  // to avoid strange output situation inside
  // bash screen.
  while (wait(NULL)) {
    if (errno == ECHILD) {
      break;
    }
  }

  return 0;
}
