#include "transform.h"


char get_char(char** prog) {
    while (**prog != 0) {
        if (strchr("<>+-,.[]", **prog) != NULL) {
            return *(*prog)++;
        }
        (*prog)++; 
    }
    return 0; 
}

void transform(char* prog, INST inst[MAX_INST_CAPACITY]) {
    char c = get_char(&prog), c1;
    int i = 0, n;
    Stack s1 ={0};
    while (c) { 
        if (i >= MAX_INST_CAPACITY) {
            fprintf(stderr, "Transform: Instruction capacity exceeded\n");
            exit(EXIT_FAILURE);
        }

        switch (c) {
            case INST_INC:
            case INST_DEC:
            case INST_MOVL:
            case INST_MOVR:
            case INST_OUT:
            case INST_IN: {
                n = 1;
                char c1;

                while ((c1 = get_char(&prog)) == c) {
                    n++;
                }

                inst[i].opcode = c;
                inst[i].operand = n;
                i++;
                c = c1; 
                break;
            }

            case INST_JMP_IF_ZERO: {
                if(s1.sp >= MAX_STACK_CAPACITY ){
                    fprintf(stderr, "Transform: Stack overflow");
                    exit(EXIT_FAILURE);
                }

                s1.stack[s1.sp++] = i; 

                inst[i].opcode = c;
                inst[i].operand = 0;
                i++;

                c = get_char(&prog);
                break;
            }

            case INST_JMP_IF_NONZERO: { 
                if(s1.sp <= 0){
                    fprintf(stderr, "Transform: Stack underflow, unmatched brackets");
                    exit(EXIT_FAILURE);
                }

                n = s1.stack[--s1.sp];

                inst[i].opcode = c;
                inst[i].operand = n;
                i++;
                inst[n].operand = i;


                c = get_char(&prog);
                break;
            }

            default:
                fprintf(stderr, "Transform: Unexpected character: %d", c);
                exit(EXIT_FAILURE);
        }
    }
}
