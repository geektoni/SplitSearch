#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "splitsearch.h"


/* Handlers */

// Define bool type
typedef enum { false, true } bool;

// Read from pipe updated max-value. Update it, if specified
void updatepipe (int pfd[], int * max_value, bool update, int update_value ) {
  // Read value from pipe
  read(pfd[0],max_value,sizeof(int));
  // if update is true than decrement max_value of updadate_value
  if (update) {
    * max_value -= update_value;
  }
  // rewrite updated value into pipe
  write(pfd[1],max_value,sizeof(int));
}

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
  free(tmp);
  return status;
}

// Search recursively into a file for a specific occurrence
// of an element, given in the value argument. It will return 0
// if we find something and -1 if not.
int * search(char * file, int begin, int end, char * value, int pfd[]) {
  int * status = malloc(sizeof(int)); *status = 0;
  int * max_value = malloc(sizeof(int));
  updatepipe(pfd,max_value,false,0);

  if (*max_value == 0) {
    free(max_value);
    return status;
  }
  int middle = (begin+end)/2;
  char * result = malloc(sizeof(char));
  if (begin == end) {
    int fd = open(file, O_RDONLY);
    read_line(fd, result, begin);
    if (strcmp(result,value) == 0) {
      *status = begin+1;
      updatepipe(pfd,max_value,true,1);
    }
  } else if (begin < end) {
    int pid = fork();
    if (pid==0) {
      status = search(file, begin, middle, value, pfd);
    } else if (pid==-1) {
      printf("Linear");
      int * counter = malloc(sizeof(int));
      status = linearsearch(file, begin, end, value, counter);
      updatepipe(pfd,max_value,true,*counter);
      free(counter);
    } else {
      int return_status = 0;
      waitpid(pid, &return_status, 0);
      if (WIFEXITED(return_status)) {
        if (WEXITSTATUS(return_status) == 1) {
          // Nothing found
          updatepipe(pfd,max_value,false,0);
          status = search(file, middle+1, end, value, pfd);
        } else {
          // Found a value
          updatepipe(pfd,max_value,false,0);
          status = search(file, middle+1, end, value, pfd);
        }
      }
    }
  }
  free(result);
  free(max_value);
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
  free(buffer);
  return counter;
}

int * linearsearch(char * file, int begin, int end, char * value, int * max) {
  char * buffer = malloc(sizeof(char));
  int counter = 0;
  int * status = malloc(sizeof(int));
  *status = 0;
  int fd = open(file, O_RDONLY);
  while (begin <= end) {
    read_line(fd, buffer, begin);
    if (strcmp(buffer, value) == 0) {
      status = realloc(status, sizeof(int)*counter+1);
      status[counter] = begin+1;
      counter++; begin++;
    }
  }
  *max = counter;
  free(buffer);
  return status;
}
