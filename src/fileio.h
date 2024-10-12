#ifndef FILEIO
#define FILEIO

#include <stdio.h>
#include <stdlib.h>
#include <error.h>

void usage(char* s);
size_t calculate_file_size(FILE* fd);
char* read_from_file(char* path);

#endif