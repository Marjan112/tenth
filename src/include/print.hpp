#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <ostream>
#include <fstream>
#include <termcolor.hpp>

#define UNIMPLEMENTED(...)                                                              \
    do {                                                                                \
        tenth::print_info(__VA_ARGS__, " File: ", __FILE__, ". Line: ", __LINE__, "."); \
        exit(1);                                                                        \
    } while(false)

namespace tenth {
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
        print(std::cout, termcolor::grey<char>, "[USAGE]: ", termcolor::reset<char>, program, " [filename]");
        // print(std::cout, "<options>: <--int | --com> (--int for interpret | --com for compile)");
    }
}

#endif /* PRINT_HPP */