#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "transform.h"
#include "bfdef.h"
#include "bfexec.h"


int main(int argc, char* argv[]) {
    printf("Starting program...\n");
    if (argc < 2) usage(argv[0]);
    
    char* prog = read_from_file(argv[1]);
    printf("%s\n", prog);

    INST inst[MAX_INST_CAPACITY] = {
        0
    };

    transform(prog, inst);
    free(prog);

    for(int i = 0 ; i < MAX_INST_CAPACITY ; i++ ){
        if(inst[i].opcode == INST_EXIT) break;
        printf("%c {%d} \n", inst[i].opcode, inst[i].operand);
    }

    bfexec(inst);
    
    return EXIT_SUCCESS ;
}