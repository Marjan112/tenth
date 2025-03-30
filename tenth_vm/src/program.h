#pragma once

#define PROGRAM_CAPACITY 128

#include "stack/stack.h"

typedef enum {
    INST_,
    INST_PUSH,
    INST_PLUS,
    INST_MINUS,
    INST_MUL,
    INST_DIV,
    INST_LT,
    INST_GT,
    INST_LTEQ,
    INST_GTEQ,
    INST_EQ,
    INST_NOT_EQ,
    INST_DUMP,
    INST_SHOW,
    INST_DUP,
    INST_DROP,
    INST_SWAP,
    INST_OVER,
    INST_ROT,
    INST_EXIT,
    INST_INC,
    INST_DEC,
    INST_PRINT,
    INST_JMP,
} Inst_Type;

typedef struct {
    Inst_Type type;
    Stack_Value value;
} Inst;

typedef struct {
    Inst inst[PROGRAM_CAPACITY];
    size_t ip;
    size_t inst_count;
} Program;