#include "interp.h"

#include <stdio.h>

bool step(program_state_t* state, token_t* program, int8_t* data) {
    token_t code = program[state->pc];

    if (code.type == 0) return false;

    uint32_t loops = 1;

    switch (code.type) {
        case '+': data[state->dc] += code.count; break;
        case '-': data[state->dc] -= code.count; break;

        case '>': state->dc += code.count; break;
        case '<': state->dc -= code.count; break;

        case '.': putc(data[state->dc], stdout); break;
        case ',': data[state->dc] = getc(stdin); break;

        case '[':
                  if (data[state->dc]) break;
                  state->pc += code.count;
                  break;

        case ']':
                  if (!data[state->dc]) break;

                  state->pc -= code.count;
                  break;

        default:
                  break;
    }

    state->pc++;

    return true;

}
