#ifndef BFDEF
#define BFDEF

#define MAX_INST_CAPACITY 4096

typedef enum {
        INST_EXIT = 0,
        INST_INC = '+',
        INST_DEC = '-',
        INST_MOVL = '<',
        INST_MOVR = '>',
        INST_IN = ',',
        INST_OUT = '.',
        INST_JMP_IF_ZERO = '[',
        INST_JMP_IF_NONZERO = ']'
}
INST_TYPE;

typedef struct {
    INST_TYPE opcode;
    int operand;
}
INST;


#endif