#ifndef OPCODES_HPP
#define OPCODES_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

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
        DEC,
        DEFINE_WORD
    };

    struct instruction {
        opcodes opcode;
        std::variant<int, float, std::string> value;
    };

    typedef std::vector<instruction> program_t;

    std::unordered_map<std::string, opcodes> opcode_map = {
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
        {"sizeof", SIZEOF},
        {"inc", INC},
        {"dec", DEC}
    };
}

#endif /* OPCODES_HPP */