#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "createoutputfile.h"

/*
  This function returns the file descriptor associated with the output file
  specified by user where the program's output should be printed
*/

FILE * createoutputfile (char * file_name) {

  FILE *out = fopen(file_name,"w");
  printf("output file created\n" );

  return out;

}
