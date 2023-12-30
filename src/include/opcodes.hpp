#ifndef OPCODES_HPP
#define OPCODES_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

namespace tenth {
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
        SIZEOF,
        INC,
        DEC
    };

    struct instruction {
        opcodes opcode;
        std::variant<int, float, std::string> value;
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
        {"sizeof", SIZEOF},
        {"inc", INC},
        {"dec", DEC}
    };
}

#endif /* OPCODES_HPP */