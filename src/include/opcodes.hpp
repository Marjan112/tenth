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
        SYSCALL1,
        SYSCALL2,
        SYSCALL3,
        SYSCALL4,
        SYSCALL5,
        SYSCALL6
    };

    struct instruction {
        opcodes opcode;
        std::variant<int, std::string> value;
    };

    typedef std::vector<instruction> program_t;

    const std::unordered_map<std::string, opcodes> opcode_map = {
        {   "+",             PLUS       },
        {   "-",             MINUS      },
        {   "*",             MUL        },
        {   "/",             DIV        },
        {   "<",             LT         },
        {   ">",             GT         },
        {   "=",             EQ         },
        {   ".",             DUMP       },
        {   "show",          SHOW       },
        {   "dup",           DUP        },
        {   "drop",          DROP       },
        {   "swap",          SWAP       },
        {   "over",          OVER       },
        {   "rot",           ROT        },
        {   "emit",          EMIT       },
        {   "exit",          EXIT       },
        {   "sizeof",        SIZEOF     },
        {   "syscall1",      SYSCALL1   },
        {   "syscall2",      SYSCALL2   },
        {   "syscall3",      SYSCALL3   },
        {   "syscall4",      SYSCALL4   },
        {   "syscall5",      SYSCALL5   },
        {   "syscall6",      SYSCALL6   }
    };
}

#endif /* OPCODES_HPP */