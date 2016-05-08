#ifndef SPLITSEARCH_H
#define SPLITSEARCH_H

int append(char * from, char * to);
int length(int fd);
int empty(char * s);
int read_line(int fd, char * buffer, int line_number);
int * search(char * file, int begin, int end, char * value, int pfd [], int verbose_mode);
int * linearsearch(char * file, int begin, int end, char * value, int * max);

#endif
