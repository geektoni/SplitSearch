#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int countlines(FILE* f){
    int counter = 0;
    int buffer = 0;
    do {
      buffer = fgetc(f);
      if (buffer == '\n'){
        counter++;
      }
    } while (buffer != EOF);
    fclose(f);
    return counter;
}


int main(int argc, char **argv) {

    int pfd[2];

    FILE *f;
    if (argc != 2) {
      printf("\nUsage: %s FILE\n\n", argv[0]);
      exit(1);
    }

    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(1);
    }

    f = fopen (argv[1], "r");

    int count = 0;
    int pid = fork();
    if (pid == 0 ) {
        printf("%s\n", "I'm the Son" );
        count = countlines(f);
        printf("%i\n", count );
        int buff1[1] = {count};
        write(pfd[1],buff1,sizeof(int));
        close(pfd[1]);

    } else {
      waitpid(pid,&count,0);
      printf("%s\n", "I'm the Father" );
      int s[1];
      read(pfd[0], s, sizeof(s));
      printf("%i first lines\n", s[0] );
      close(pfd[0]);

    }

    return 0;
}
