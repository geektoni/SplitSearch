int better_read_line (int fd, char * buffer, int line_number, int * offsets) {
  int status = 0;
  read(fd, buffer, offsets[line_number];
  return status;
}


// Search recursively into a file for a specific occurrence
// of an element, given in the value argument. It will return 0
// if we find something and -1 if not.
int * search(char * file, int begin, int end, char * value, int pfd[], int * offsets) {
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
      status = search(file, begin, middle, value, pfd, offsets);
    } else if (pid==-1) {
      printf("Linear");
      int * counter = malloc(sizeof(int));
      status = linearsearch(file, begin, end, value, counter);
      updatepipe(pfd,max_value,true,*counter);
    } else {
      int return_status = 0;
      waitpid(pid, &return_status, 0);
      if (WIFEXITED(return_status)) {
        if (WEXITSTATUS(return_status) == 1) {
          // Nothing found
          updatepipe(pfd,max_value,false,0);
          status = search(file, middle+1, end, value, pfd, offsets);
        } else {
          // Found a value
          updatepipe(pfd,max_value,false,0);
          status = search(file, middle+1, end, value, pfd, offsets);
        }
      }
    }
  }
  return status;
}


// Return the number of rows into a file (given as file descriptor)
int length(int fd, int * offsets) {

  // index for get the [i]_th line from [offsets]
  int i = 1;
  // off counts the number of bytes to get to the [i]_th line
  int off = 0;

  offsets = malloc(sizeof(int));

  // Set offsets for first line = 0
  offsets[0] = 0;
  printf("Offset for %i line= %i\n",1,offsets[0]);

  int counter = 0;
  char * buffer = malloc(sizeof(char));
  while(read(fd, buffer, sizeof(char))) {
    if (*buffer == '\n') {
      counter++;
      // Write offset for line no_[counter] in [i] position of [offsets] array
      offsets[i] = off+1;
      printf("Offset for %i line= %i\n",i+1,offsets[i]);
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
