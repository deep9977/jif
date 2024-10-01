#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<error.h>

#define MAX_INST_CAPACITY 50
#define MAX_STACK_CAPACITY 20


typedef enum {
    INST_EXIT = '0',
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

void usage(char* s) {
    fprintf(stderr, "Usage: %s <prog.bf>", s);
    exit(EXIT_FAILURE);
}

size_t calculate_file_size(FILE* fd) {
    if (fseek(fd, 0, SEEK_END)) {
        perror("fseek fail");
        exit(EXIT_FAILURE);
    }

    size_t file_size = ftell(fd);
    if (file_size <= 0) {
        perror("ftell fail");
        exit(EXIT_FAILURE);
    }

    rewind(fd);

    return file_size;
}

char* read_from_file(char* path) {
    FILE* fd = fopen(path, "r");
    if (fd == NULL) {
        perror("Could not open the file");
        exit(EXIT_FAILURE);
    }

    size_t file_size = calculate_file_size(fd);
    char* buffer = (char* ) malloc(file_size + 1);

    size_t fr = fread(buffer, 1, file_size, fd);
    if (fr != file_size) {
        perror("Could not read from file");
        exit(EXIT_FAILURE);
    }

    fclose(fd);
    return buffer;
}

char get_char(char* prog) {
    while (*prog != 0) {
        if (strchr("<>+-,.[]", *prog) != NULL) {
            return *prog; 
        }
        prog++; 
    }
    return 0; 
}

void transform(char* prog, INST inst[MAX_INST_CAPACITY]) {
    char c = get_char(prog++), c1;
    int i = 0;

    while (c) { 
        if (i >= MAX_INST_CAPACITY) {
            fprintf(stderr, "Instruction capacity exceeded\n");
            exit(EXIT_FAILURE);
        }

        switch (c) {
            case '+':
            case INST_DEC:
            case INST_MOVL:
            case INST_MOVR:
            case INST_OUT:
            case INST_IN:
                int n = 1;
                char c1;

                while ((c1 = get_char(prog++)) == c) {
                    n++;
                }

                inst[i].opcode = c;
                inst[i].operand = n;
                i++;
                c = c1; 
                break;
            

                
            default:
                printf("\ntodo");
                exit(0);
        }
    }
}


int main(int argc, char* argv[]) {
    printf("Starting program...\n");
    if (argc < 2) usage(argv[0]);
    
    char* prog = read_from_file(argv[1]);
    printf("%s\n", prog);

    INST inst[MAX_INST_CAPACITY] = {
        0
    };

    transform(prog, inst);
    
    for(int i = 0 ; i < MAX_INST_CAPACITY ; i++ ){
        printf("%c {%d} \n", inst[i].opcode, inst[i].operand);
    }


    return 0;
}