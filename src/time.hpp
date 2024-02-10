#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <utility>
#include "print.hpp"

template<typename FunctionT, typename... ArgsT>
void measure_time(FunctionT function, ArgsT&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    function(std::forward<ArgsT>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration(end - start);
    print_info("Execution Time: ", termcolor::white<char>, duration.count(), termcolor::reset<char>, "ms.");
}

#endif /* TIME_HPP */