#include "loader.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>

token_t* tokenize(int8_t* arr);
void optimize(token_t* in);

void optimize(token_t* tokens) {
    int i = 0;

    while(tokens[i].type != 0) {
        if (tokens[i].type != '[') {
            i++;
            continue;
        }

        uint32_t offset = 0;
        uint16_t loops = 0;

        do {
            switch (tokens[i + offset++].type) {
                case '[': loops++; break;
                case ']': loops--; break;
            }
        } while (loops > 0);

        offset--;

        tokens[i].count = offset;
        tokens[i + offset].count = offset;

        i++;
    }
}

token_t* tokenize(int8_t* input) {
    token_t* tokens = malloc(sizeof(token_t) * MAX_PROGRAM_SIZE);

    if (tokens == NULL) {
        puts("alloc error");
        exit(0);
    }

    int i = 0, j = 0;

    int8_t code = 0;
    int16_t count = 1;

    while(input[i] != 0) {
        if (code == 0) {
            code = input[i++];
            continue;
        }

        if (code == '[' || code == ']' || code == '.' || code == ',') {
            tokens[j++] = (token_t){ .type = code, .count = 1 };
            code = input[i++];
            continue;
        }

        if (code == input[i]) {
            count++;
        } else {
            tokens[j++] = (token_t){ .type = code, .count = count }; 
            count = 1;
            code = input[i];
        }

        i++;
    }


    return tokens;
}

bool read_program(token_t** tokens, char* file_path) {
    int8_t buffer[MAX_PROGRAM_SIZE];

    FILE* source = fopen(file_path, "r");

    if (source == NULL) {
        printf("cant find file %s\n", file_path);
        return false;
    }
    int p = 0;

    while (1) {
        int c = fgetc(source);

        if (c == -1) break;

        switch (c) {
            case '+': 
            case '-':
            case '>':
            case '<':
            case '.':
            case ',':
            case '[':
            case ']':
                buffer[p++] = c;
                break;

            default:
                break;
        }

        if (p >= MAX_PROGRAM_SIZE) break;
    }

    fclose(source);

    *tokens = tokenize(buffer);
    optimize(*tokens);

    return true;
}
