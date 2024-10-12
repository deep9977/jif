#include "bfexec.h"


void map_exec(unsigned char bytes[], size_t size){

    char *ptr = mmap(NULL, size+1, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED){
        perror("BFEXEC: mmap failed");
        exit(EXIT_FAILURE);
    }
    memcpy(ptr, bytes, size);

    void (*func)() = (void(*)())ptr;

    (*func)();
}

void bfexec(INST inst[MAX_INST_CAPACITY]){

    for(int ip = 0 ; ip <= MAX_INST_CAPACITY; ip++){
        
        switch (inst[ip].opcode) {

            case INST_EXIT: 
                unsigned char bytes[] = { 0xb8, 0x3c, 0x00, 0x00, 0x00,       //mov rax, 60
                    0xbf, 0x07, 0x00, 0x00, 0x00,                             //mov rdi, 0
                    0x0f, 0x05                                                          //syscall    
                };

                map_exec(bytes, sizeof(bytes));
                break;



            case INST_INC:
            case INST_DEC:
            case INST_MOVL:
            case INST_MOVR:
            case INST_IN:
            case INST_OUT:
            case INST_JMP_IF_ZERO:
            case INST_JMP_IF_NONZERO:
        
        }


     


    }    


}