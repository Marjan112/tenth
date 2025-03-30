#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

enum inst_type {
    PUSH,
    PLUS,
    MINUS,
    MUL,
    DIV,
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
    JMP,
    DEBUG_PRINT
};

typedef std::variant<int, float, std::string> stack_value_t;

struct inst {
    inst_type type;
    stack_value_t value;
};
    
typedef std::vector<inst> program_t;

const std::unordered_map<std::string, inst_type> OPCODES = {
    {"+", PLUS},
    {"-", MINUS},
    {"*", MUL},
    {"/", DIV},
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
    {"jmp", JMP},
    {"debug_print", DEBUG_PRINT}
};