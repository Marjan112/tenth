#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <fstream>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    void compile_program(std::string filename, const program_t& program) {
        UNIMPLEMENTED("Compiling is not implemented yet.");
        #ifdef WIN32
        print_error("Compiling on windows is not supported yet.");
        #endif /* WIN32 */
    }
}

#endif /* COMPILER_HPP */