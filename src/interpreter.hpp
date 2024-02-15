#pragma once

#include "opcodes.hpp"
#include "stack.hpp"
#include "print.hpp"

void interpret_program(const program_t& program) {
    std::vector<stack_value_t> stack;

    for(const auto& op : program) {
        switch(op.opcode) {
            case PUSH: {
                stack.push_back(op.value);
                break;
            }
            case PLUS: {
                check_stack_size(stack);
                if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a + b);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a + b);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a + b);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
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
                check_stack_size(stack);
                if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(b - a);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(b - a);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(b - a);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(b - a);
                    }
                }
                break;
            }
            case MUL: {
                check_stack_size(stack);
                if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a * b);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a * b);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a * b);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a * b);
                    }
                }
                break;
            }
            case DIV: {
                check_stack_size(stack);
                if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        if(a == 0) {
                            print_error("div: cannot divide by zero");
                            exit(1);
                        }
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(b / a);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        if(a == 0) {
                            print_error("div: cannot divide by zero");
                            exit(1);
                        }
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(b / a);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        if(a == 0) {
                            print_error("div: cannot divide by zero");
                            exit(1);
                        }
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(b / a);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        if(a == 0) {
                            print_error("div: cannot divide by zero");
                            exit(1);
                        }
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(b / a);
                    }
                }
                break;
            }
            case LT: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    stack.push_back(std::get<std::string>(*(stack.end() - 1)) < std::get<std::string>(*(stack.end() - 2)) ? -1 : 0);
                } else if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) < std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) < std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) < std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) < std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    }
                }
                break;
            }
            case GT: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    stack.push_back(std::get<std::string>(*(stack.end() - 1)) > std::get<std::string>(*(stack.end() - 2)) ? -1 : 0);
                } else if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) > std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) > std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) > std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) > std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    }
                }
                break; 
            }
            case EQ: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    stack.push_back(std::get<std::string>(*(stack.end() - 1)) == std::get<std::string>(*(stack.end() - 2)) ? -1 : 0);
                } else if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) == std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) == std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) == std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) == std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    }
                }
                break;
            }
            case NOT_EQ: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    stack.push_back(std::get<std::string>(*(stack.end() - 1)) != std::get<std::string>(*(stack.end() - 2)) ? -1 : 0);
                } else if(std::holds_alternative<int>(*(stack.end() - 1))) {
                    if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) != std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) != std::get<int>(*(stack.end() - 1)) ? -1 : 0);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        stack.push_back(std::get<float>(*(stack.end() - 2)) != std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        stack.push_back(std::get<int>(*(stack.end() - 2)) == std::get<float>(*(stack.end() - 1)) ? -1 : 0);
                    }
                }
                break;
            }
            case DUMP: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<std::string>(stack.back())) {
                    print(std::cout, std::get<std::string>(stack.back()));
                } else if(std::holds_alternative<int>(stack.back())) {
                    print(std::cout, std::get<int>(stack.back()));
                } else if(std::holds_alternative<float>(stack.back())) {
                    print(std::cout, std::get<float>(stack.back()));
                } else if(std::holds_alternative<size_t>(stack.back())) {
                    print(std::cout, std::get<size_t>(stack.back()));
                }
                stack.pop_back();
                break; 
            }
            case SHOW: {
                print_stack(stack);
                break;
            }
            case DUP: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<std::string>(stack.back())) {
                    stack.push_back(std::get<std::string>(stack.back()));
                } else if(std::holds_alternative<int>(stack.back())) {
                    stack.push_back(std::get<int>(stack.back()));
                } else if(std::holds_alternative<float>(stack.back())) {
                    stack.push_back(std::get<float>(stack.back()));
                }
                break;
            }
            case DROP: {
                check_stack_size(stack, 1);
                stack.pop_back();
                break;
            }
            case SWAP: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                        auto a = std::get<std::string>(stack.back());
                        stack.pop_back();
                        auto b = std::get<std::string>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<std::string>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<std::string>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
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
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                        auto a = std::get<int>(stack.back());
                        stack.pop_back();
                        auto b = std::get<std::string>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<float>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<int>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                        auto a = std::get<float>(stack.back());
                        stack.pop_back();
                        auto b = std::get<std::string>(stack.back());
                        stack.pop_back();
                        stack.push_back(a);
                        stack.push_back(b);
                    }
                }
                break;
            }
            case OVER: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(*(stack.begin() + 1))) {
                    auto a = std::get<std::string>(*(stack.begin() + 1));
                    stack.push_back(a);
                } else if(std::holds_alternative<int>(*(stack.begin() + 1))) {
                    auto a = std::get<int>(*(stack.begin() + 1));
                    stack.push_back(a);
                } else if(std::holds_alternative<float>(*(stack.begin() + 1))) {
                    auto a = std::get<float>(*(stack.begin() + 1));
                    stack.push_back(a);
                }
                break;
            }
            case ROT: {
                check_stack_size(stack, 3);
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
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }  else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                        if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<int>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    }
                } else if(std::holds_alternative<float>(*(stack.end() - 1))) {
                    if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<std::string>(*(stack.end() - 2))) {
                        if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<float>(stack.back());
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
                        } else if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<int>(*(stack.end() - 2))) {
                        if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<int>(stack.back());
                            stack.pop_back();
                            auto c = std::get<std::string>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        }
                    } else if(std::holds_alternative<float>(*(stack.end() - 2))) {
                        if(std::holds_alternative<float>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<float>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<int>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
                            stack.pop_back();
                            auto c = std::get<int>(stack.back());
                            stack.pop_back();
                            stack.push_back(b);
                            stack.push_back(a);
                            stack.push_back(c);
                        } else if(std::holds_alternative<std::string>(*(stack.end() - 3))) {
                            auto a = std::get<std::string>(stack.back());
                            stack.pop_back();
                            auto b = std::get<float>(stack.back());
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
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    print(std::cout, static_cast<char>(std::get<int>(stack.back())));
                    stack.pop_back();
                } else {
                    print_error("emit: invalid parameter, must be an interger");
                    exit(1);
                }
                break;
            }
            case EXIT: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    exit(std::get<int>(stack.back()));
                } else {
                    print_error("exit: invalid parameter, must be an integer");
                    exit(1);
                }
                break;
            }
            case SIZEOF: {
                check_stack_size(stack, 1);
                size_t size = 0;
                if(std::holds_alternative<int>(stack.back())) {
                    size = sizeof(int);
                } else if(std::holds_alternative<std::string>(stack.back())) {
                    size = std::get<std::string>(stack.back()).size();
                } else if(std::holds_alternative<float>(stack.back())) {
                    size = sizeof(float);
                }
                stack.push_back(size);
                break;
            }
            case INC: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    auto a = std::get<int>(stack.back());
                    stack.pop_back();
                    stack.push_back(a + 1);
                } else if(std::holds_alternative<float>(stack.back())) {
                    auto a = std::get<float>(stack.back());
                    stack.pop_back();
                    stack.push_back(a + 1.0f);
                } else if(std::holds_alternative<std::string>(stack.back())) {
                    print_error("dec: cannot use strings");
                    exit(1);
                }
                break;
            }
            case DEC: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    auto a = std::get<int>(stack.back());
                    stack.pop_back();
                    stack.push_back(a - 1);
                } else if(std::holds_alternative<float>(stack.back())) {
                    auto a = std::get<float>(stack.back());
                    stack.pop_back();
                    stack.push_back(a - 1.0f);
                } else if(std::holds_alternative<std::string>(stack.back())) {
                    print_error("dec: cannot use strings");
                    exit(1);
                }
                break;
            }
            case PRINT: {
                check_stack_size(stack, 1);

                std::stringstream output;

                for(const auto& elem : stack) {
                    if(std::holds_alternative<int>(elem)) {
                        output << std::get<int>(elem);
                    } else if(std::holds_alternative<float>(elem)) {
                        output << std::get<float>(elem);
                    } else if(std::holds_alternative<std::string>(elem)) {
                        output << std::get<std::string>(elem);
                    } else if(std::holds_alternative<size_t>(elem)) {
                        output << std::get<size_t>(elem);
                    }
                    stack.pop_back();
                }

                print<false>(std::cout, output.str());
                break;
            }
        }
    }
}