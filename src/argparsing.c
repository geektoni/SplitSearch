#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparsing.h"

/*
  Returns either if arg is a marker when <marker> parameter is NULL
  or if arg is equal tu a marker specified in parameter <marker>
*/
int isMarker (char* arg, char* marker) {

  char* simbols [] = {"-v", "-i", "-o", "-r"};    // Accepted Markers
  int res = 0;                                    // Return result

  int j;
  for (j = 0; j < 4; j++) {
    if (strcmp(arg,simbols[j]) == 0){
      //Checks whether arg is the specified <marker>
      if (!(marker==NULL) && (strcmp(arg,marker) == 0)){
          res = 1;
      // otherwise returns that arg IS a marker
      } else if (marker == NULL) {
          res = 1;
      }
    }
  }
  return res;
}

/*
  Return <args> vector which contains position in user's input of:
  -  args[0] => input_file
  -  args[1] => value_to_find
  -  args[2] => output_file
  -  args[3] => maximum_value_of_results
  which if not present are equal to '-1'
  and located with markers:
  - i
  - v
  - o
  - r
  read from command line.

  <-v> and <-i> must be present otherwise the function prints an error.
*/
int* argParser(int argc, char **argv){

    // args vector which will be returned
    int* args = malloc(sizeof(int)*4);

    int k;
    for (k = 0; k < 4; k++) {
      //Set default value for each marker
      args[k] = -1;
    }
    char* simbols [] = {"-v", "-i", "-o", "-r"};

    // Check whether number of arguments is suitable
    if (argc < 5 || argc > 9){
      exitonerror();
    }

    int i = 1;
    // Read from command line and search if any of <markers> is present in user's input
    while (i < argc){
      if (isMarker(argv[i],simbols[0])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (args[0] != -1) exitonerror();
          args[0] = i+1;
        } else {
          exitonerror();
        }
      } else if (isMarker(argv[i],simbols[1])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (args[1] != -1) exitonerror();
          args[1] = i+1;
        } else {
          exitonerror();
        }
      } else if (isMarker(argv[i],simbols[2])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (args[2] != -1) exitonerror();
          args[2] = i+1;
        } else {
          exitonerror();
        }
      } else if (isMarker(argv[i],simbols[3])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (args[3] != -1) exitonerror();
          args[3] = i+1;
        } else {
          exitonerror();
        }
      }
      i++;
    }

    return args;
}

/*
  Prints error message with helper <help> when input from command line is not correct
*/
void exitonerror() {
  // Help message for correct usage
  char help [] = "Usage ./executable -v [value_to_search]\n -i [input_file]\n (optional)\n -o [output_file]\n -r [number_occurrences]\n";

  printf("Wrong arguments\n%s",help);
  exit(1);
}
