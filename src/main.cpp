#include "include/parser.hpp"
#include "include/interpreter.hpp"

int main(int argc, char** argv) {
    if(argc < 2) {
        tenth::print_usage(argv[0]);
        tenth::print_error("No filename provided.");
        return 1;
    }

    tenth::interpret_program(tenth::load_program(argv[1]));
    return 0;
}