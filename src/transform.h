#ifndef TRANSFORM
#define TRANSFORM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bfdef.h"


#define MAX_STACK_CAPACITY 20


typedef struct{
    size_t stack[MAX_STACK_CAPACITY];
    size_t sp;
}Stack;


char get_char(char** prog);
void transform(char* prog, INST inst[MAX_INST_CAPACITY]);

#endif