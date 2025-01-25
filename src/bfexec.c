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
    unsigned int ip = 0;
    unsigned int* ip_add = &ip;


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
        0xb3, 0x00,                                                                 //mov rbx, inst.operand    
        0x00, 0x18,                                                        //add BYTE [rax], bl
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_INC_bytes[2], &head_add, sizeof(char*));
    unsigned char* ptr_do_INST_INC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_INC_bytes));
    void (*do_INST_INC)() = (void(*)())ptr_do_INST_INC_bytes;

    unsigned char do_INST_DEC_bytes[] = {
         0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0x49, 0x8b ,0x00,                                                       //mov rax, [r8]
        0xb3, 0x00,                                                                //mov bl, inst.operand    
        0x28, 0x18,                                                        //sub BYTE [rax], bl
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_DEC_bytes[2], &head_add, sizeof(char*));
    unsigned char* ptr_do_INST_DEC_bytes = make_exec(do_INST_INC_bytes, sizeof(do_INST_DEC_bytes));
    void (*do_INST_DEC)() = (void(*)())ptr_do_INST_DEC_bytes;

    unsigned char do_INST_IN_bytes[] = {
        0x49, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov r8, address_of_head
        0xb8, 0x00, 0x00, 0x00, 0x00,                                           //mov rax, 0    
        0xbf, 0x00, 0x00, 0x00, 0x0,                                            //mov rdi, 0
        0x49, 0x8b, 0x30,                                                       //mov [r8], rsi
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
        0xbf, 0x01, 0x00, 0x00, 0x0,                                            //mov rdi, 1
        0x49, 0x8b, 0x30,                                                        //mov [r8], rsi
        0xba, 0x01, 0x00, 0x00, 0x0,                                            //mov rdx, 1 
        0x0f, 0x05,                                                             //syscall
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_OUT_bytes[2], &head_add, sizeof(char**));
    unsigned char* ptr_do_INST_OUT_bytes = make_exec(do_INST_OUT_bytes, sizeof(do_INST_OUT_bytes));
    void (*do_INST_OUT)() = (void(*)())ptr_do_INST_OUT_bytes;

    unsigned char do_INST_JMP_IF_ZERO_bytes[] = {
         0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand  
        0x48, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rcx, address_of_ip
        0x48, 0x8b, 0x10,                                                       //mov rdx, [rax]
        0x48, 0x83, 0x3a, 0x00,                                                 //cmp QWORD [rdx], 0
        0x75, 0x03,                                                             //jne ret
        0x48, 0x89, 0x19,                                                       //mov [rcx], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_JMP_IF_ZERO_bytes[2], &head_add, sizeof(char**));
    memcpy(&do_INST_JMP_IF_ZERO_bytes[17], &ip_add, sizeof(unsigned int*));
    unsigned char* ptr_do_INST_JMP_IF_ZERO_bytes = make_exec(do_INST_JMP_IF_ZERO_bytes, sizeof(do_INST_JMP_IF_ZERO_bytes));
    void (*do_INST_JMP_IF_ZERO)() = (void(*)())ptr_do_INST_JMP_IF_ZERO_bytes;

    unsigned char do_INST_JMP_IF_NONZERO_bytes[] = {
        0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rax, address_of_head
        0xbb, 0x00, 0x00, 0x00, 0x00,                                           //mov rbx, inst.operand  
        0x48, 0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //mov rcx, address_of_ip
        0x48, 0x8b, 0x10,                                                       //mov rdx, [rax]
        0x48, 0x83, 0x3a, 0x00,                                                 //cmp QWORD [rdx], 0
        0x74, 0x03,                                                             //je ret
        0x48, 0x89, 0x19,                                                       //mov [rcx], rbx
        0xc3                                                                    //ret      
    };
    memcpy(&do_INST_JMP_IF_NONZERO_bytes[2], &head_add, sizeof(char**));
    memcpy(&do_INST_JMP_IF_NONZERO_bytes[17], &ip_add, sizeof(unsigned int*));
    unsigned char* ptr_do_INST_JMP_IF_NONZERO_bytes = make_exec(do_INST_JMP_IF_NONZERO_bytes, sizeof(do_INST_JMP_IF_NONZERO_bytes));
    void (*do_INST_JMP_IF_NONZERO)() = (void(*)())ptr_do_INST_JMP_IF_NONZERO_bytes;


    for(ip = 0 ; ip < MAX_INST_CAPACITY; ip++){
   
        switch (inst[ip].opcode) {

            case INST_EXIT: 
                
                goto cleanup;

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
            
                uint8_t num = (uint8_t) inst[ip].operand;
            
                memcpy(&do_INST_INC_bytes[14], &num, 1);
                memcpy(ptr_do_INST_INC_bytes, &do_INST_INC_bytes, sizeof(do_INST_INC_bytes));

                (*do_INST_INC)();
                
                break;

            case INST_DEC:
                            
                num = (uint8_t) inst[ip].operand;
                memcpy(&do_INST_DEC_bytes[14], &num, 1);
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

                memcpy(&do_INST_JMP_IF_ZERO_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_JMP_IF_ZERO_bytes, &do_INST_JMP_IF_ZERO_bytes, sizeof(do_INST_JMP_IF_ZERO_bytes));

                (*do_INST_JMP_IF_ZERO)();

                break;

	        case INST_JMP_IF_NONZERO:

                memcpy(&do_INST_JMP_IF_NONZERO_bytes[11], &inst[ip].operand, sizeof(int));
                memcpy(ptr_do_INST_JMP_IF_NONZERO_bytes, &do_INST_JMP_IF_NONZERO_bytes, sizeof(do_INST_JMP_IF_NONZERO_bytes));

                (*do_INST_JMP_IF_NONZERO)();

                break;

            default:

                goto cleanup;
        
        }
    }    

cleanup: 

    munmap(ptr_do_INST_MOVR_bytes, sizeof(do_INST_MOVR_bytes));
    munmap(ptr_do_INST_MOVL_bytes, sizeof(do_INST_MOVL_bytes));
    munmap(ptr_do_INST_INC_bytes, sizeof(do_INST_INC_bytes));   
    munmap(ptr_do_INST_DEC_bytes, sizeof(do_INST_DEC_bytes));
    munmap(ptr_do_INST_OUT_bytes, sizeof(do_INST_OUT_bytes));
    munmap(ptr_do_INST_IN_bytes, sizeof(do_INST_IN_bytes));
    munmap(ptr_do_INST_JMP_IF_NONZERO_bytes, sizeof(do_INST_JMP_IF_NONZERO));
    munmap(ptr_do_INST_JMP_IF_ZERO_bytes, sizeof(do_INST_JMP_IF_ZERO));
        
    return;
}