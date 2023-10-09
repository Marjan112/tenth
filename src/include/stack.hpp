#ifndef STACK_UTILS
#define STACK_UTILS

#include <vector>
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
        void print_stack(const std::vector<std::variant<ArgsT...>>& stack) {
            if(stack.empty()) {
                print(std::cout, "(empty)");
                return;
            }
            for(const auto& elem : stack) {
                if(std::holds_alternative<int>(elem)) {
                    print<false>(std::cout, std::get<int>(elem), " ");
                } else if(std::holds_alternative<float>(elem)) {
                    print<false>(std::cout, std::get<float>(elem), " ");
                } else if(std::holds_alternative<std::string>(elem)) {
                    print<false>(std::cout, "\"", std::get<std::string>(elem), "\" ");
                }
            }
            print(std::cout, '\n');
        }
    }
}

#endif /* STACK_UTILS */