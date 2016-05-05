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
  return status;
}

// Search recursively into a file for a specific occurrence
// of an element, given in the value argument. It will return 0
// if we find something and -1 if not.
int search(char * file, int begin, int end, char * value, int pfd[]) {
  // PIPE ----
  int * max_value = malloc(sizeof(int));

  // read(pfd[0],max_value,sizeof(int));
  // write(pfd[1],max_value,sizeof(int));

  updatepipe(pfd,max_value,false,0);

  if (*max_value == 0) {
    return 0;
  }
  int middle = (begin+end)/2, status=0;
  char * result = malloc(sizeof(char));
  if (begin == end) {
    int fd = open(file, O_RDONLY);
    read_line(fd, result, begin);
    if (strcmp(result,value) == 0) {
      status = begin+1;
      // read(pfd[0],max_value,sizeof(int));
      // // write pipe
      // *max_value -= 1;
      // write(pfd[1],max_value,sizeof(int));
      updatepipe(pfd,max_value,true,1);

    }
  } else if (begin < end) {
    int pid = fork();
    if (pid==0) {
      status = search(file, begin, middle, value, pfd);
    } else {
      int return_status = 0;
      waitpid(pid, &return_status, 0);
      if (WIFEXITED(return_status)) {
        if (WEXITSTATUS(return_status) == 1) {
          // Nothing found
          read(pfd[0],max_value,sizeof(int));
          write(pfd[1],max_value,sizeof(int));
          status = search(file, middle+1, end, value, pfd);
        } else {
          // Found a value
          // read(pfd[0],max_value,sizeof(int));
          // write(pfd[1],max_value,sizeof(int));
          updatepipe(pfd,max_value,false,0);
          status = search(file, middle+1, end, value, pfd);
        }
      }
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
