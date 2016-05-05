#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparsing.h"

int isMarker (char* arg, char* marker) {
  char* simbols [] = {"-v", "-i", "-o", "-r"};
  int res = 0;

  for (int i = 0; i < 4; i++) {
    if (strcmp(arg,simbols[i]) == 0){
      if (!(marker==NULL) && (strcmp(arg,marker) == 0)){
          res = 1;
      } else if (marker == NULL) {
          res = 1;
      }
    }
  }

  return res;
}


int* argParser(int argc, char **argv){

    char help [] = "Usage ./executable -v [value_to_search]\n -i [input_file]\n (optional)\n -o [output_file]\n -r [number_occurrences]\n";
    int* result = malloc(sizeof(int)*4);
    for (int i = 0; i < 4; i++) {
      result[i] = -1;
    }
    char* simbols [] = {"-v", "-i", "-o", "-r"};

    // Check whether number of arguments is suitable
    if (argc < 5 || argc > 9){
      exitonerror(help);
    }

    int i = 1;
    while (i < argc){
      if (isMarker(argv[i],simbols[0])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (result[0] != -1) exitonerror(help);
          result[0] = i+1;
        } else {
          exitonerror(help);
        }
      } else if (isMarker(argv[i],simbols[1])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (result[1] != -1) exitonerror(help);
          result[1] = i+1;
        } else {
          exitonerror(help);
        }
      } else if (isMarker(argv[i],simbols[2])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (result[2] != -1) exitonerror(help);
          result[2] = i+1;
        } else {
          exitonerror(help);
        }
      } else if (isMarker(argv[i],simbols[3])){
        if (argv[i+1]!= NULL && !isMarker(argv[i+1],NULL)){
          if (result[3] != -1) exitonerror(help);
          result[3] = i+1;
        } else {
          exitonerror(help);
        }
      }
      i++;
    }

    return result;
}

void exitonerror(char * help) {
  printf("Wrong arguments\n%s",help);
  exit(1);
}
