#pragma once

#include "termcolor.hpp"

#define UNIMPLEMENTED(...)                                                              \
    do {                                                                                \
        print_info(__VA_ARGS__, " File: ", __FILE__, ". Line: ", __LINE__, "."); \
        exit(1);                                                                        \
    } while(false)

template<bool newline = true, typename StreamT, typename... ArgsT>
void print(StreamT&& stream, ArgsT&&... args) {
    (stream << ... << args);
    if(newline == true) {
        stream << "\n";
    }
}

template<typename... ArgsT>
void print_error(ArgsT&&... args) {
    print(std::cerr, termcolor::red<char>, "[ERROR]: ", termcolor::reset<char>, args...);
}

template<typename... ArgsT>
void print_warning(ArgsT&&... args) {
    print(std::cout, termcolor::yellow<char>, "[WARNING]: ", termcolor::reset<char>, args...);
}

template<typename... ArgsT>
void print_info(ArgsT&&... args) {
    print(std::cout, termcolor::blue<char>, "[INFO]: ", termcolor::reset<char>, args...);
}

void print_usage(const std::string& program) {
    print(std::cout, termcolor::white<char>, "[USAGE]: ", termcolor::reset<char>, program, " [filename]");
}