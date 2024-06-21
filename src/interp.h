#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t type;
    uint32_t count;
} token_t;

typedef struct {
    uint32_t pc;
    uint32_t dc;
} program_state_t;

bool step(program_state_t* state, token_t* program, int8_t* data);
