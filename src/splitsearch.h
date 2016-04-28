#ifndef SPLITSEARCH_H
#define SPLITSEARCH_H

int append(char * from, char * to);
int length(int fd);
int empty(char * s);
int read_line(int fd, char * buffer, int line_number);
int search(int fd, int begin, int end, char * value);

#endif
