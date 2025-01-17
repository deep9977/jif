#include "bfexec.h"

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
    char** head_add = &head;


    unsigned char do_INST_EXIT_bytes[] = {
        0xb8, 0x3c, 0x00, 0x00, 0x00,                              //mov rax, 60
        0xbf, 0x46, 0x00, 0x00, 0x00,                              //mov rdi, 0
        0x0f, 0x05                                                 //syscall    
    };
    unsigned char* ptr_do_INST_EXIT_bytes = make_exec(do_INST_EXIT_bytes, sizeof(do_INST_EXIT_bytes));
    void (*do_INST_EXIT)() = (void(*)()) ptr_do_INST_EXIT_bytes;

    unsigned char do_INST_MOVR_bytes[] = {
        0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand    
        0x48,0x01, 0x18,                                                        //add QWORD [rax], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_MOVR_bytes[2], &head_add, sizeof(char**));
    unsigned char* ptr_do_INST_MOVR_bytes = make_exec(do_INST_MOVR_bytes, sizeof(do_INST_MOVR_bytes));
    void (*do_INST_MOVR)() = (void(*)())ptr_do_INST_MOVR_bytes;

    unsigned char do_INST_MOVL_bytes[] = {
        0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand    
        0x48,0x29, 0x18,                                                        //sub QWORD [rax], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_MOVL_bytes[2], &head_add, sizeof(char**));
    unsigned char* ptr_do_INST_MOVL_bytes = make_exec(do_INST_MOVL_bytes, sizeof(do_INST_MOVL_bytes));
    void (*do_INST_MOVL)() = (void(*)())ptr_do_INST_MOVL_bytes;

    unsigned char do_INST_INC_bytes[] = {
        0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0x49, 0x8b ,0x00,                                                       //mov rax, [r8]
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand    
        0x48,0x01, 0x18,                                                        //add QWORD [rax], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_INC_bytes[2], &head_add, sizeof(char*));
    unsigned char* ptr_do_INST_INC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_INC_bytes));
    void (*do_INST_INC)() = (void(*)())ptr_do_INST_INC_bytes;

    unsigned char do_INST_DEC_bytes[] = {
         0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0x49, 0x8b ,0x00,                                                       //mov rax, [r8]
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand    
        0x48,0x29, 0x18,                                                        //sub QWORD [rax], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_DEC_bytes[2], &head_add, sizeof(char*));
    unsigned char* ptr_do_INST_DEC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_DEC_bytes));
    void (*do_INST_DEC)() = (void(*)())ptr_do_INST_DEC_bytes;

    unsigned char do_INST_IN_bytes[] = {
        0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0xb8, 0x00, 0x00, 0x00, 0x00,                                           //mov rax, 0    
        0xbf, 0x00, 0x00, 0x00, 0x0,                                            //add rdi, 0
        0x49, 0x8b, 0x30,                                                        //mov [r8], rsi
        0xba, 0x01, 0x00, 0x00, 0x0,                                            //mov rdx, 1 
        0x0f, 0x05,                                                             //syscall
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_IN_bytes[2], &head_add, sizeof(char**));
    unsigned char* ptr_do_INST_IN_bytes = make_exec(do_INST_IN_bytes, sizeof(do_INST_IN_bytes));
    void (*do_INST_IN)() = (void(*)())ptr_do_INST_IN_bytes;


    unsigned char do_INST_OUT_bytes[] = {
        0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0xb8, 0x01, 0x00, 0x00, 0x00,                                           //mov rax, 1    
        0xbf, 0x01, 0x00, 0x00, 0x0,                                            //add rdi, 1
        0x49, 0x8b, 0x30,                                                         //mov [r8], rsi
        0xba, 0x01, 0x00, 0x00, 0x0,                                            //mov rdx, 1 
        0x0f, 0x05,                                                             //syscall
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_OUT_bytes[2], &head_add, sizeof(char**));
    unsigned char* ptr_do_INST_OUT_bytes = make_exec(do_INST_OUT_bytes, sizeof(do_INST_OUT_bytes));
    void (*do_INST_OUT)() = (void(*)())ptr_do_INST_OUT_bytes;


    for(int ip = 0 ; ip < MAX_INST_CAPACITY; ip++){
     
        switch (inst[ip].opcode) {

            case INST_EXIT: 
                
                (*do_INST_EXIT)();

            case INST_MOVL:

                memcpy(&do_INST_MOVL_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_MOVL_bytes, &do_INST_MOVL_bytes, sizeof(do_INST_MOVL_bytes));

                (*do_INST_MOVL)();

                break;

            case INST_MOVR:

                memcpy(&do_INST_MOVR_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_MOVR_bytes, &do_INST_MOVR_bytes, sizeof(do_INST_MOVR_bytes));

                (*do_INST_MOVR)();

                break;

            case INST_INC:
            
                memcpy(&do_INST_INC_bytes[14], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_INC_bytes, &do_INST_INC_bytes, sizeof(do_INST_INC_bytes));

                (*do_INST_INC)();
                
                break;

            case INST_DEC:
                
                memcpy(&do_INST_DEC_bytes[14], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_DEC_bytes, &do_INST_DEC_bytes, sizeof(do_INST_DEC_bytes));

                (*do_INST_DEC)();

                break;

            case INST_IN:
                
                for(int i = 0 ; i < inst[ip].operand ; i++) {
                    (*do_INST_IN)();
                    getchar();      //handeling \n after input
                }

                break;

            case INST_OUT:
                           
                for(int i = 0 ; i < inst[ip].operand ; i++) {
                    (*do_INST_OUT)();
                }

                break;
                
            case INST_JMP_IF_ZERO:
            case INST_JMP_IF_NONZERO:
            default:
        
        }
    }    
}