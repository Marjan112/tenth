#include "include/parser.hpp"
#include "include/interpreter.hpp"
#include "include/compiler.hpp"
#include "include/print.hpp"

int main(int argc, char** argv) {
    if(argc < 3) {
        tenth::print_usage(argv[0]);
        tenth::print_error("No filename provided.");
        return 1;
    }

    if(!strcmp(argv[1], "--int")) {
        tenth::interpret_program(tenth::load_program(argv[2]));
    } else if(!strcmp(argv[1], "--com")) {
        tenth::compile_program(argv[2], tenth::load_program(argv[2]));
    }

    return 0;
}