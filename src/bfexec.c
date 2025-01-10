#include "bfexec.h"
#include "bfdef.h"
#include <stdio.h>
#include <string.h>


void* make_exec(unsigned char* bytes, size_t size){
    
    unsigned char* ptr = mmap(
        NULL,
        size, 
        PROT_EXEC | PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS, 
        -1, 
        0
    ); 

    if(ptr == MAP_FAILED){
        perror("BFEXEC: mmap failed");
        exit(EXIT_FAILURE);
    }

    memcpy(ptr, bytes, size);

    return ptr;
}

void bfexec(INST inst[MAX_INST_CAPACITY]){

    char tape[30000] = {0};
    char* head = tape;


    unsigned char do_INST_EXIT_bytes[] = { 0xb8, 0x3c, 0x00, 0x00, 0x00,       //mov rax, 60
        0xbf, 0x46, 0x00, 0x00, 0x00,                             //mov rdi, 0
       0x0f, 0x05                                                          //syscall    
    };
    unsigned char* ptr_do_INST_EXIT_bytes = make_exec(do_INST_EXIT_bytes, sizeof(do_INST_EXIT_bytes));
    void (*do_INST_EXIT)() = (void(*)()) ptr_do_INST_EXIT_bytes;


    unsigned char do_INST_INC_bytes[] = {
        0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,           //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                       //mov rbx, inst.operand    
        0x48,0x01, 0x18,                                                            //add QWORD [rax], rbx
        0xc3                                                                                     //ret      
    };
    memcpy(&do_INST_INC_bytes[2], &head, sizeof(char*));
    unsigned char* ptr_do_INST_INC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_INC_bytes));
    void (*do_INST_INC)() = (void(*)())ptr_do_INST_INC_bytes;


    unsigned char do_INST_DEC_bytes[] = {
        0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,           //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                       //mov rbx, inst.operand    
        0x48,0x29, 0x18,                                                            //add QWORD [rax], rbx
        0xc3                                                                                     //ret      
    };
    memcpy(&do_INST_DEC_bytes[2], &head, sizeof(char*));
    unsigned char* ptr_do_INST_DEC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_DEC_bytes));
    void (*do_INST_DEC)() = (void(*)())ptr_do_INST_DEC_bytes;





    for(int ip = 0 ; ip < MAX_INST_CAPACITY; ip++){
     
        switch (inst[ip].opcode) {

            case INST_EXIT: 
                
                (*do_INST_EXIT)();

            case INST_MOVR:
            case INST_MOVL:
            case INST_INC:
            
                memcpy(&do_INST_INC_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_INC_bytes, do_INST_INC_bytes, sizeof(do_INST_INC_bytes));

                for(int i = 0 ; i< sizeof(do_INST_INC_bytes); i++){
                    printf("%x ", do_INST_INC_bytes[i]);
                }

                (*do_INST_INC)();
                printf(" %d", *head);
                
                break;

            case INST_DEC:
                
                memcpy(&do_INST_DEC_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_DEC_bytes, do_INST_DEC_bytes, sizeof(do_INST_DEC_bytes));

                (*do_INST_DEC)();
                printf(" %d", *head);
                
                break;

            case INST_IN:
            case INST_OUT:
            case INST_JMP_IF_ZERO:
            case INST_JMP_IF_NONZERO:
            default:
        
        }
    }    
}