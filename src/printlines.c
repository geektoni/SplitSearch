#include <stdio.h>
#include <stdlib.h>
#include "printlines.h"

/*
  This function check whether the program's output has to be printet on stoutput
  or in a specific file.
*/

void printlines (int * buffer, FILE * out) {
  if (out == NULL) {
    printf("%i\n", *buffer);
  } else {
    char * buff = malloc(sizeof(char)*100);
    sprintf(buff, "%i", *buffer);
    fprintf(out, "%s\n", buff);
  }
}
