#ifndef ARGPARSING_H
#define ARGPARSING_H

  int isMarker (char* arg, char* marker);
  int hasdefaults(int * args);
  void exitonerror();
  int * argParser(int argc, char **argv);

#endif
