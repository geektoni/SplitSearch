#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparsing.h"

int isMarker (char* arg, char* marker) {
  char* simbols [] = {"-v", "-i", "-o", "-r"};
  int res = 0;
  int i=0;
  for (i = 0; i < 4; i++) {
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
    int j=0;
    for (j = 0; j < 4; j++) {
      result[j] = -1;
    }
    char* simbols [] = {"-v", "-i", "-o", "-r"};


    // Check whether number of arguments is suitable
    if (argc < 5 || argc > 9){
      printf("Wrong arguments\n%s",help);
      exit(0);
    }

    int i = 1;
    while (i < argc){
      if (isMarker(argv[i],simbols[0])){
        if ((argv[i+1]!= NULL) && !isMarker(argv[i+1],NULL)){
          result[0] = i+1;
        } else {
          printf("Wrong arguments\n%s",help);
          exit(1);
        }
      } else if (isMarker(argv[i],simbols[1])){
        if ((argv[i+1]!= NULL) && !isMarker(argv[i+1],NULL)){
          result[1] = i+1;
        } else {
          printf("Wrong arguments\n%s",help);
          exit(1);
        }
      } else if (isMarker(argv[i],simbols[2])){
        if ((argv[i+1]!= NULL) && !isMarker(argv[i+1],NULL)){
          result[2] = i+1;
        } else {
          printf("Wrong arguments\n%s",help);
          exit(1);
        }
      } else if (isMarker(argv[i],simbols[3])){
        if ((argv[i+1]!= NULL) && !isMarker(argv[i+1],NULL)){
          result[3] = i+1;
        } else {
          printf("Wrong arguments\n%s",help);
          exit(1);
        }
      }

      i++;
    }

    return result;
}
