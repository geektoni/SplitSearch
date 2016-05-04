#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "createFileOutput.h"

int outputFile (int * arg, char **argv) {

  char * file_name = argv[arg[2]];

  int fd = open(file_name,O_WRONLY);

  return fd;

}
