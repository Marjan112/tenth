#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <variant>

#include "opcodes.hpp"
#include "stack.hpp"
#include "print.hpp"

namespace tenth {
    void interpret_program(const program_t& program) {
        std::vector<std::variant<long long, std::string>> stack;

        for(const auto& op : program) {
            switch(op.opcode) {
                case PUSH: {
                    if(op.token_type == INT) {
                        stack.push_back(op.longlong_value);
                    } else if(op.token_type == STR) {
                        stack.push_back(op.string_value);
                    }
                    break;
                }
                case PLUS: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            auto a = std::get<long long>(stack.back());
                            stack.pop_back();
                            auto b = std::get<long long>(stack.back());
                            stack.pop_back();
                            stack.push_back(a + b);
                        }
                    }
                    break;
                }
                case MINUS: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            auto a = std::get<long long>(stack.back());
                            stack.pop_back();
                            auto b = std::get<long long>(stack.back());
                            stack.pop_back();
                            stack.push_back(b - a);
                        }
                    }
                    break;
                }
                case MUL: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            auto a = std::get<long long>(stack.back());
                            stack.pop_back();
                            auto b = std::get<long long>(stack.back());
                            stack.pop_back();
                            stack.push_back(a * b);
                        }
                    }
                    break;
                }
                case DIV: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            auto a = std::get<long long>(stack.back());
                            stack.pop_back();
                            auto b = std::get<long long>(stack.back());
                            stack.pop_back();
                            stack.push_back(b / a);
                        }
                    }
                    break;
                }
                case LT: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot compare strings.");
                        exit(1);
                    }
                    stack.push_back(std::get<long long>(stack[stack.size() - 2]) < std::get<long long>(stack[stack.size() - 1]) ? -1 : 0);
                    break; 
                }
                case GT: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot compare strings.");
                        exit(1);
                    }
                    stack.push_back(std::get<long long>(stack[stack.size() - 2]) > std::get<long long>(stack[stack.size() - 1]) ? -1 : 0);
                    break; 
                }
                case EQ: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot compare strings.");
                        exit(1);
                    }
                    stack.push_back(std::get<long long>(stack[stack.size() - 2]) == std::get<long long>(stack[stack.size() - 1]) ? -1 : 0);
                    break; 
                }
                case DUMP: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print(std::cout, std::get<std::string>(stack.back()));
                    } else if(std::holds_alternative<long long>(stack.back())) {
                        print(std::cout, std::get<long long>(stack.back()));
                    }
                    stack.pop_back();
                    break; 
                }
                case SHOW: {
                    __internal::print_stack(std::move(stack));
                    break;
                }
                case DUP: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        stack.push_back(std::get<std::string>(stack.back()));
                    } else if(std::holds_alternative<long long>(stack.back())) {
                        stack.push_back(std::get<long long>(stack.back()));
                    }
                    break;
                }
                case DROP: {
                    __internal::check_stack_size(stack, 1);
                    stack.pop_back();
                    break;
                }
                case SWAP: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                        if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(a);
                            stack.push_back(b);
                        }
                    } else if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            auto a = std::get<long long>(stack.back());
                            stack.pop_back();
                            auto b = std::get<long long>(stack.back());
                            stack.pop_back();
                            stack.push_back(a);
                            stack.push_back(b);
                        }
                    }
                    break;
                }
                case OVER: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(*(stack.begin() + 1))) {
                        auto a = std::get<std::string>(*(stack.begin() + 1));
                        stack.push_back(a);
                    } else if(std::holds_alternative<long long>(*(stack.begin() + 1))) {
                        auto a = std::get<long long>(*(stack.begin() + 1));
                        stack.push_back(a);
                    }
                    break;
                }
                case ROT: {
                    __internal::check_stack_size(stack, 3);
                    if(std::holds_alternative<long long>(*(stack.end() - 1))) {
                        if(std::holds_alternative<long long>(*(stack.end() - 2))) {
                            if(std::holds_alternative<long long>(*(stack.end() - 3))) {
                                auto a = std::get<long long>(stack.back());
                                stack.pop_back();
                                auto b = std::get<long long>(stack.back());
                                stack.pop_back();
                                auto c = std::get<long long>(stack.back());
                                stack.pop_back();
                                stack.push_back(b);
                                stack.push_back(a);
                                stack.push_back(c);
                            }
                        }
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                        if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                            if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                                auto a = std::get<std::string>(stack.back());
                                stack.pop_back();
                                auto b = std::get<std::string>(stack.back());
                                stack.pop_back();
                                auto c = std::get<std::string>(stack.back());
                                stack.pop_back();
                                stack.push_back(b);
                                stack.push_back(a);
                                stack.push_back(c);
                            }
                        }
                    }
                    break;
                }
                case EMIT: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                        print_error("You cannot use emit with strings.");
                        exit(1);
                    }
                    auto a = std::get<long long>(stack.back());
                    stack.pop_back();
                    break;
                }
                case QUIT: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<long long>(stack.back())) {
                        exit(static_cast<int>(std::get<long long>(stack.back())));
                    }
                    break;
                }
            }
        }
    }
}

#endif /* INTERPRETER_HPP */