#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "splitsearch.h"
#include "argparsing.h"
#include <limits.h>

int main(int argc, char * argv[]) {

  // Check if the user supplied enough
  // flags to run the script.
  int * arg = argParser(argc, argv);

  // Read the entire file to estimate
  // its number of lines
  int file = open(argv[arg[1]], O_RDONLY);
  int max = length(file);
  close(file);

  int S = 0;
  int *R = &S;

  //writing pipe
  int pf[2];
  //reading pipe
  // int cf[2];
  if (pipe(pf) == -1)
    {
      perror("pipe");
      exit(1);
    }
  // if (pipe(cf) == -1)
  //   {
  //     perror("pipe");
  //     exit(1);
  //   }


  // Check if user set -r value
  if (arg[3] != -1){
    // set max values to display -r
    S = atoi(argv[arg[3]]);
    printf("writing r value%i\n", S );

    write(pf[1],R,sizeof(int));
  } else {
    *R = 100;
    printf("writing r value %i\n", *R );
    write(pf[1],R,sizeof(int));
  }

  printf("Perform search\n");

  // Perform a search for the specific value
  search(argv[arg[1]], 0, max, argv[arg[0]], pf);

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
