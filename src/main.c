#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"
#include "interp.h"
#include "loader.h"


int main(int argc, char** argv) {
    if (argc <= 1) {
        puts("bf {file}");
        exit(0);
    }

    token_t* program = NULL;

    if (!read_program(&program, argv[1]))
        exit(0);

    program_state_t state = { 0 };

    int8_t data[MAX_DATA_SIZE];

    puts("|| START ||");

    while (step(&state, program, data));

    puts("\n||  END  ||");

    free(program);
}

