#include <stdio.h>
#include <stdlib.h>
#include "printlines.h"

/*
  This function check whether the program's output has to be printet on stoutput
  or in a specific file.

  Input:
  - buffer : array with result's line number
  - out : file in which print the output. Can be NULL

  Outut:
  - stdout : prints buffer's content
  - out: if not NULL prints buffer's content in output file
*/
void printlines (int * buffer, FILE * out) {
  if (out == NULL) {
    printf("Value found in line: %i\n", *buffer);
  } else {
    char * buff = malloc(sizeof(char)*100);
    // Convert int buffer to char buffer
    sprintf(buff, "%i", *buffer);
    fprintf(out, "Value found in line: %s\n", buff);
  }
}
