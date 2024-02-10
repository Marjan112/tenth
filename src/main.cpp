#include "Parser.hpp"
#include "interpreter.hpp"

int main(int argc, char** argv) {
    if(argc < 2) {
        print_usage(argv[0]);
        print_error("No filename provided.");
        return 1;
    }

    Parser file_parser(argv[1]);
    interpret_program(file_parser.parse());
    return 0;
}