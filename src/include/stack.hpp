#ifndef STACK_UTILS
#define STACK_UTILS

#include <iostream>
#include <vector>
#include <stack>
#include <variant>

#include "print.hpp"

namespace tenth {
    namespace __internal {
        template<typename... ArgsT>
        void check_stack_size(const std::vector<std::variant<ArgsT...>>& stack, std::size_t size = 2) {
            if(stack.size() < size) {
                print_error("Stack underflow.");
                exit(1);
            }
        }

        template<typename... ArgsT>
        void print_stack(std::vector<std::variant<ArgsT...>>&& stack) {
            if(stack.empty()) {
                std::cout << "(empty)\n";
                return;
            }
            for(auto& elem : stack) {
                if(std::holds_alternative<long long>(elem)) {
                    std::cout << std::get<long long>(elem) << " ";
                } else if(std::holds_alternative<std::string>(elem)) {
                    std::cout << std::get<std::string>(elem) << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

#endif /* STACK_UTILS */