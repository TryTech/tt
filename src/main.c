
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/lex.h"
#include "../include/token.h"


char* file_to_string(const FILE* file) { 
    fseek(file, 0, SEEK_END);
    long lenght = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = calloc(lenght + 1, sizeof(char));
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, lenght, file);
    buffer[lenght] = '\0';
    fclose(file);
    return buffer;
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }

    FILE * file = fopen(argv[1], "r");

    if (!file) {
        fprintf(stderr, "Error: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    char *buffer = file_to_string(file);

    lex(buffer);

    return 0;
}
