#ifndef BFEXEC
#define BFEXEC

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "bfdef.h"

void* make_exec(unsigned char*, size_t);
void bfexec(INST inst[MAX_INST_CAPACITY]);

#endif