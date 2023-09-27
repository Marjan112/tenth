#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "opcodes.hpp"
#include "stack.hpp"
#include "print.hpp"

namespace tenth {
    void interpret_program(const program_t& program) {
        std::vector<std::variant<int, std::string>> stack;

        for(const auto& op : program) {
            switch(op.opcode) {
                case PUSH: {
                    stack.push_back(op.value);
                    break;
                }
                case PLUS: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(a + b);
                        }
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                        if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b + a);
                        }
                    }
                    break;
                }
                case MINUS: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b - a);
                        }
                    }
                    break;
                }
                case MUL: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(a * b);
                        }
                    }
                    break;
                }
                case DIV: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
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
                    stack.push_back(std::get<int>(stack[stack.size() - 2]) < std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                    break; 
                }
                case GT: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot compare strings.");
                        exit(1);
                    }
                    stack.push_back(std::get<int>(stack[stack.size() - 2]) > std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                    break; 
                }
                case EQ: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        stack.push_back(std::get<std::string>(stack[stack.size() - 2]) == std::get<std::string>(stack[stack.size() - 1]) ? -1 : 0);
                    } else if(std::holds_alternative<int>(stack.back())) {
                        stack.push_back(std::get<int>(stack[stack.size() - 2]) == std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                    }
                    break;
                }
                case NOT_EQ: {
                    __internal::check_stack_size(stack);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        stack.push_back(std::get<std::string>(stack[stack.size() - 2]) != std::get<std::string>(stack[stack.size() - 1]) ? -1 : 0);
                    } else if(std::holds_alternative<int>(stack.back())) {
                        stack.push_back(std::get<int>(stack[stack.size() - 2]) != std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                    }
                    break;
                }
                case DUMP: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        print(std::cout, std::get<std::string>(stack.back()));
                    } else if(std::holds_alternative<int>(stack.back())) {
                        print(std::cout, std::get<int>(stack.back()));
                    }
                    stack.pop_back();
                    break; 
                }
                case SHOW: {
                    __internal::print_stack(stack);
                    break;
                }
                case DUP: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<std::string>(stack.back())) {
                        stack.push_back(std::get<std::string>(stack.back()));
                    } else if(std::holds_alternative<int>(stack.back())) {
                        stack.push_back(std::get<int>(stack.back()));
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
                    } else if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
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
                    } else if(std::holds_alternative<int>(*(stack.begin() + 1))) {
                        auto a = std::get<int>(*(stack.begin() + 1));
                        stack.push_back(a);
                    }
                    break;
                }
                case ROT: {
                    __internal::check_stack_size(stack, 3);
                    if(std::holds_alternative<int>(*(stack.end() - 1))) {
                        if(std::holds_alternative<int>(*(stack.end() - 2))) {
                            if(std::holds_alternative<int>(*(stack.end() - 3))) {
                                auto a = std::get<int>(stack.back());
                                stack.pop_back();
                                auto b = std::get<int>(stack.back());
                                stack.pop_back();
                                auto c = std::get<int>(stack.back());
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
                    auto a = std::get<int>(stack.back());
                    stack.pop_back();
                    break;
                }
                case EXIT: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<int>(stack.back())) {
                        exit(std::get<int>(stack.back()));
                    } else {
                        print_error("Invalid input parameter.");
                        exit(1);
                    }
                    break;
                }
                case SIZEOF: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<int>(stack.back())) {
                        print(std::cout, sizeof(std::get<int>(stack.back())));
                    } else if(std::holds_alternative<std::string>(stack.back())) {
                        print(std::cout, std::get<std::string>(stack.back()).size());
                    }
                }
                case INC: {
                    __internal::check_stack_size(stack, 1);
                    if(std::holds_alternative<int>(stack.back())) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a + 1);
                    } else if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot use inc on strings.");
                        exit(1);
                    }
                    break;
                }
                case DEC: {
                    if(std::holds_alternative<int>(stack.back())) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a - 1);
                    } else if(std::holds_alternative<std::string>(stack.back())) {
                        print_error("Cannot use dec on strings.");
                        exit(1);
                    }
                    break;
                }
            }
        }
    }
}

#endif /* INTERPRETER_HPP */