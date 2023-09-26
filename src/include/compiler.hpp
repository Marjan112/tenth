#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <fstream>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    void compile_program(std::string filename, const program_t& program) {
        UNIMPLEMENTED("Compiling is not implemented yet.");

        std::ofstream output_file(filename);    
    }
}

#endif /* COMPILER_HPP */