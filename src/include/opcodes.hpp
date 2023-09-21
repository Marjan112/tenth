#ifndef OPCODES_HPP
#define OPCODES_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace tenth {
    enum opcodes {
        PUSH,
        PLUS,
        MINUS,
        MUL,
        DIV,
        LT,
        GT,
        EQ,
        DUMP,
        SHOW,
        DUP,
        DROP,
        SWAP,
        OVER,
        ROT,
        EMIT,
        QUIT
    };

    enum token {
        WORD,
        INT,
        STR
    };

    struct instruction {
        opcodes opcode;
        long long longlong_value;
        std::string string_value;
        token token_type;
    };

    typedef std::vector<instruction> program_t;

    const std::unordered_map<std::string, opcodes> opcode_map = {
        {"+", PLUS},
        {"-", MINUS},
        {"*", MUL},
        {"/", DIV},
        {"<", LT},
        {">", GT},
        {"=", EQ},
        {".", DUMP},
        {"show", SHOW},
        {"dup", DUP},
        {"drop", DROP},
        {"swap", SWAP},
        {"over", OVER},
        {"rot", ROT},
        {"emit", EMIT},
        {"quit", QUIT}
    };
}

#endif /* OPCODES_HPP */