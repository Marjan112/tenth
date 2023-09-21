#include <csignal>

#include "include/parser.hpp"
#include "include/interpreter.hpp"
#include "include/print.hpp"
#include "include/time.hpp"

int main(int argc, char** argv) {
    if(argc == 1) {
        std::signal(SIGINT, [](int signal) {
            tenth::print(std::cout, "To exit, push exit code and call quit.");
        });

        while(true) {
            std::string words;
            tenth::print<false>(std::cout, termcolor::blue<char>, "tenth> ");
            std::getline(std::cin, words); // this is not finished
        }
    } else if(argc > 1) {
        tenth::measure_time(tenth::interpret_program, tenth::load_program(argv[1]));
    }
    return 0;
}