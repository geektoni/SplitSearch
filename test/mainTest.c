#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "splitsearch.h"
#include "argparsing.h"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char * argv[]) {


  // Check if the user supplied enough
  // flags to run the script.
  int * arg = argParser(argc, argv);

  // Generate FIFO
  int FIFO1 = mkfifo("FIFO", FILE_MODE);
  int FIFO2 = mkfifo("FIFO", FILE_MODE);


  // Read the entire file to estimate
  // its number of lines (it exit if the file
  // doesn't exist,)
  int file = open(argv[arg[1]], O_RDONLY);
  if (file == -1) {
    perror(argv[arg[1]]);
    exit(-1);
  }
  int max = length(file);
  close(file);

int found = 0;
while (found == 0){
  int f1 = fork();
  if (getpid() == f1){
    //primogenito
    int begin = 0;
    int middle = length/2;
    if (begin == end){
      int result = read_line();
      found = true;
      write(FIFO2,result);
    }
  } else if (getpid() == f1 && (middle2 < end)){
    //primogenito
    int f2 = fork();
    wait(f2);
    read(FIFO2);
    if (r > 0){
      int middle2 = length/2 +1;
      int end = length;
      if (middle2 == end){
        read_line();
        write(FIFO1,result);
        found = true;
      }
    }
  } else {
    //padre
    wait(f2);
    read(fifo2);
    print(result);
  }

  }




  return 0;
}
