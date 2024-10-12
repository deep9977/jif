#include "fileio.h"

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
