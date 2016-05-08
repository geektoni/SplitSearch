#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparsing.h"

/* Helpers */


/*
  Returns either if arg is a marker when <marker> parameter is NULL
  or if arg is equal tu a marker specified in parameter <marker>

  Input:
    - arg : i_th argument in user's input
    - marker : marker to compare <arg> with. (Can be NULL)
  Output:
    - 0 : if one of arg is not in user's input
    - 1 : if user's input is correct
*/
int isMarker (char * arg, char * marker) {

  char* simbols [] = {"-v", "-i", "-o", "-r", "--verbose"};    // Accepted Markers
  int res = 0;                                                 // Return result

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
  Check if user's input has required default markers <-v> and <-i>
  Returns 1 if correct otherwise returns 0.

  Input:
    - args : vector with index of user's input's position in command line
  Output:
    - 0 : if
*/
  int hasdefaults(int * args) {

    // Defaults that must be present for prgram to work properly
    int res = 0;

    if ( (args[0] != -1) && (args[1] != -1) ){
        res = 1;
    }

    return res;
  }

/*
  Prints error message with helper <help> when input from command line is not correct

  Input:
    - none
  Output:
    - stdout : prints correct user's input
*/
void exitonerror() {
  // Help message for correct usage
  char help [] = "Usage:\t./splitsearch -v value_to_search -i input_file\n \t[ -o output_file ]\n \t[ -r number_occurrences ]\n \t[ --verbose ]\n";

  printf("Wrong arguments\n%s",help);
  exit(1);
}


/* Main Functions */


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
  "checkdefaults" verifies that at least <-v> and <-i> are specified

  Input:
    - argc : number of user's input
    - argv : user's input
  Output:
    - exit : if wrong user's input
    - args : index of user's argument for each marker accepted
*/
int* argParser(int argc, char **argv){

    // args vector which will be returned
    int* args = malloc(sizeof(int)*5);

    int k;
    for (k = 0; k < 5; k++) {
      //Set default value for each marker
      args[k] = -1;
    }
    char* simbols [] = {"-v", "-i", "-o", "-r","--verbose"};

    // Check whether number of arguments is suitable
    if (argc < 5 || argc > 10){
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
      // Check for --verbose marker presence
      } else if (isMarker(argv[i],simbols[4])){
        // --verbose marker doesn't require an argument
        printf("verbose found" );
        if (argv[i+1] == NULL){
          if (args[4] != -1) exitonerror();
          args[4] = 1;
        } else {
          exitonerror();
        }
      }
      i++;
    }

    if (!hasdefaults(args)) {
      exitonerror();
    }

    return args;
}
