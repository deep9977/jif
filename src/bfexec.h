#ifndef BFEXEC
#define BFEXEC

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "bfdef.h"


void map_exec(unsigned char bytes[], size_t size);
void bfexec(INST inst[MAX_INST_CAPACITY]);

#endif