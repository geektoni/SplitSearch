#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "splitsearch.h"

// Set a string as empty. If the string is
// null it will return -1.
int empty(char * s) {
  if (s==NULL) return -1;
  s[0] = '\0';
  return 0;
}

// Legge una specifica linea di un file passato come
// file descriptor
int read_line(int fd, char * buffer, int line_number) {
  int status = 0, counter=-1;

  char * tmp = malloc(sizeof(char));
  buffer = realloc(buffer, sizeof(char));
  char term = '\0';

  while(read(fd, tmp, sizeof(char)) && counter < line_number) {
    if (*tmp == '\n' && counter != line_number-1) {
      counter++;
      empty(buffer);
    } else if (*tmp=='\n' && counter == line_number-1) {
      counter++;
    } else {
      append(tmp, buffer);
    }
    empty(tmp);
  }
  append(&term, buffer);
  return status;
}

// Search recursively into a file for a specific occurrence
// of an element, given in the value argument. It will return 0
// if we find something and -1 if not.
int search(int fd, int begin, int end, char * value) {
  int middle = (begin+end)/2, status=0;
  char * result = malloc(sizeof(char));
  if (begin == end) {
    read_line(fd, result, begin); // Read the specific line
    lseek(fd, 0, SEEK_SET);               // Reset the file pointer
    if (strcmp(result,value) == 0) {      // Compare the two strings
      printf("Value %s find at line %i\n", value, begin+1);
    } else {
      status = -1;
    }
  } else if (begin > end) {
    status = -1;
  } else {
    int pid = fork();
    if (pid==0) {
      status = search(fd, begin, middle, value);
    } else {
      waitpid(pid, &status, 0);
      status = search(fd, middle+1, end, value);
    }
  }
  return status;
}

// Append the first char of the form argument to the end
// of the to argument.
int append(char * from, char * to) {
  // It the from or the to arguments are null exit
  if (from == NULL || to == NULL) return -1;
  size_t len = strlen(to);
  to = realloc(to, len+1+1);
  // If the reallocation fails exit with error
  if (to == NULL) return -1;
  to[len] = from[0];
  to[len+1] = '\0';
  return 0;
}

// Return the number of rows into a file (given as file descriptor)
int length(int fd) {
  int counter = 0;
  char * buffer = malloc(sizeof(char));
  while(read(fd, buffer, sizeof(char))) {
    if (*buffer == '\n') counter++;
    empty(buffer);
  }
  return counter;
}
