#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

enum opcodes {
    PUSH,
    // TODO: Move these into separate enum for arithmetic operators
        PLUS,
        MINUS,
        MUL,
        DIV,
    // TODO: Move these into separate enum for comparison operators
        LT,
        GT,
        EQ,
        NOT_EQ,
    DUMP,
    SHOW,
    DUP,
    DROP,
    SWAP,
    OVER,
    ROT,
    EMIT,
    EXIT,
    INC,
    DEC,
    PRINT,
    JUMP,
    DEBUG_PRINT
};

typedef std::variant<int, float, std::string, size_t> stack_value_t;

struct instruction {
    opcodes opcode;
    stack_value_t value;
};
    
typedef std::vector<instruction> program_t;

const std::unordered_map<std::string, opcodes> BUILTIN_WORDS = {
    // TODO: Move these into separate map for arithmetic operators
        {"+", PLUS},
        {"-", MINUS},
        {"*", MUL},
        {"/", DIV},
    // TODO: Move these into separate map for comparison operators
        {"<", LT},
        {">", GT},
        {"=", EQ},
        {"!=", NOT_EQ},
    {".", DUMP},
    {"show", SHOW},
    {"dup", DUP},
    {"drop", DROP},
    {"swap", SWAP},
    {"over", OVER},
    {"rot", ROT},
    {"emit", EMIT},
    {"exit", EXIT},
    {"inc", INC},
    {"dec", DEC},
    {"print", PRINT},
    {"jump", JUMP},
    {"debug_print", DEBUG_PRINT}
};