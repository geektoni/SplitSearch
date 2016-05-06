#ifndef SPLITSEARCH_H
#define SPLITSEARCH_H

int append(char * from, char * to);
int empty(char * s);
int read_line(int fd, char * buffer, int line_number);
int * linearsearch(char * file, int begin, int end, char * value, int * max);

int length(int fd, int * offsets);
int * search(char * file, int begin, int end, char * value, int pfd [], int * offsets);
int better_read_line (int fd, char * buffer, int line_number, int * offsets);

#endif
