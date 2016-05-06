#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>

// Set a string as empty. If the string is
// null it will return -1.
int empty(char * s) {
  if (s==NULL) return -1;
  s[0] = '\0';
  return 0;
}

// Return the number of rows into a file (given as file descriptor)
int length(int fd, int * offsets) {

  offsets = malloc(sizeof(int));
  int off = 0;
  int i = 2;
  // Set offsets for first line = 0
  offsets[1] = 0;
  printf("Offset for %i line= %i\n",1,offsets[1]);

  int counter = 0;
  char * buffer = malloc(sizeof(char));
  while(read(fd, buffer, sizeof(char))) {
    if (*buffer == '\n') {
      counter++;
      // Write offset for line no_[counter] in [i] position of [offsets] array
      offsets[i] = off+1;
      printf("Offset for %i line= %i\n",i,offsets[i]);
      i++;
      realloc(offsets,i);
    }
    empty(buffer);
    // Increment offset 1 byte
    off++;
  }
  free(buffer);
  return counter;
}

int main(int argc, char const *argv[]) {

  int max = 0;                    // Total lines of the input file
  int * offsets = NULL;           // Array with offsets for each line

  // Read the entire file to estimate
  // its number of lines (it exit if the file
  // doesn't exist,)
  int file = open(argv[1], O_RDONLY);
  if (file == -1) {
    perror(argv[1]);
    exit(1);
  }

  max = length(file, offsets);
  close(file);


  return 0;
}
