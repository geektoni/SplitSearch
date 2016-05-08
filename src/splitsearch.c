#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "splitsearch.h"


// Define bool type
typedef enum { false, true } bool;


/* Helpers */

/*
  Read from pipe updated max-value. Update it, if <update> is TRUE

  Input:
    - pfd : pipe file descriptor.
    - max_value : max number of results to look for.
    - update : allows update of <max_value>.
    - update_value : value used for update max_value.
*/
void updatepipe (int pfd[], int * max_value, bool update, int update_value ) {
  // Read value from pipe
  read(pfd[0],max_value,sizeof(int));
  // if update is true than decrement max_value of update_value
  if (update) {
    * max_value -= update_value;
  }
  // rewrite updated value into pipe
  write(pfd[1],max_value,sizeof(int));
}

/*
  Set a string as empty.

  Input:
    - s : string to check.
  Output:
    1 : if the string is NULL.
    0 : if the string is valid.
*/
int empty(char * s) {
  if (s==NULL) return 1;
  s[0] = '\0';
  return 0;
}

/*
  Read a specific line of a file given as file descriptor.

  Input:
    - fd : file descriptor of input file.
    - buffer : buffer to store line read from file.
    - line_number : line's number to read from file.
  Output:
    - 0: If it found the line.
    - 1: If it doesn't found the line.
*/
int read_line(int fd, char * buffer, int line_number) {
  int status = 1, counter=-1;

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
      status = 0;
    }
    empty(tmp);
  }
  append(&term, buffer);
  free(tmp);
  return status;
}

/*
  Append the first char of the <from> argument to the end
  of the <to> argument.

  Input:
    - from : string to copy from.
    - to : string that will be modified.

  Output:
    - 1: if the function failed.
    - 0: if everything went fine.
*/
int append(char * from, char * to) {
  // It the from or the to arguments are null exit
  if (from == NULL || to == NULL) return 1;
  size_t len = strlen(to);
  to = realloc(to, len+1+1);
  // If the reallocation fails exit with error
  if (to == NULL) return 1;
  to[len] = from[0];
  to[len+1] = '\0';
  return 0;
}


/* Main Functions */

/*
  Return the number of rows into a file (given as file descriptor)

  Input:
    - fd: a valid file descriptor.
  Output:
    - The number of lines of the file.
*/
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

/*
  Search recursively into a file for a specific occurrence
  of an element, given in the value argument.

  Input:
    - file: the name of the file that we want to examine be
    - begin: the begin of the interval where to search in (line number).
    - end: the end of the interval where to search in (line number).
    - value: the value that we want to find.
    - pfd[]: the pipe were we will write how many occurence of the value
      we want to find.

  Output:
    - The number of the line where we have found the value.

*/
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
    close(fd);
  } else if (begin < end) {
    int pid = fork();
    if (pid==0) {
      status = search(file, begin, middle, value, pfd);
    } else if (pid==-1) {
      int * counter = malloc(sizeof(int));
      status = linearsearch(file, begin, end, value, counter);
      updatepipe(pfd,max_value,true,*counter);
      free(counter);
    } else {
      int return_status = 0;
      waitpid(pid, &return_status, 0);
      updatepipe(pfd,max_value,false,0);
      status = search(file, middle+1, end, value, pfd);
    }
  }
  free(result);
  free(max_value);
  return status;
}

/*
  When max fork number is reached and "splitsearch" is not yet finished this function
  checks if <value> is present in <file> with a linear search.

  Input:
  - file: the name of the file that we want to examine be
  - begin: the begin of the interval where to search in (line number).
  - end: the end of the interval where to search in (line number).
  - value: the value that we want to find.
  - pfd[]: the pipe were we will write how many occurence of the value
    we want to find.

  Output:
  - An integer array that will contain the line numbers where we have found
    the value passed as argument.
*/
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
