
int f1 = fork();
if (getpid() == f1) {
  //primogenito

  //secondogenito
  int f2 = fork()
  if (getpid() == f2){
    int middle1 = length/2;
    if (begin == middle1) {
      char * result = malloc(sizeof(char));
      if (begin == end) {
        int fd = open(file, O_RDONLY);
        read_line(fd, result, begin);
        if (strcmp(result,value) == 0) {
          status = begin;
        }
      }
      write (FIFO1, result);

    }
  }
}
