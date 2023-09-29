#include <iostream>
#include <string>
#include <cstring>
#include <variant>
#include <vector>
#include <fstream>
#include <regex>

#include "include/termcolor.hpp"

enum opcodes {
    PUSH,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LT,
    GT,
    EQ,
    NOT_EQ,
    DUMP,
    SHOW,
    DUP,
    DROP,
    SWAP,
    OVER,
    ROT,
    EMIT,
    EXIT,
    SIZEOF,
    INC,
    DEC
};

struct instruction {
    opcodes opcode;
    std::variant<int, std::string> value;
};

typedef std::vector<instruction> program_t;

std::unordered_map<std::string, opcodes> opcode_map = {
    {"+", PLUS},
    {"-", MINUS},
    {"*", MUL},
    {"/", DIV},
    {"<", LT},
    {">", GT},
    {"=", EQ},
    {"!=", NOT_EQ},
    {".", DUMP},
    {"show", SHOW},
    {"dup", DUP},
    {"drop", DROP},
    {"swap", SWAP},
    {"over", OVER},
    {"rot", ROT},
    {"emit", EMIT},
    {"exit", EXIT},
    {"sizeof", SIZEOF},
    {"inc", INC},
    {"dec", DEC}
};

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

bool is_str_str(const std::string& str) {
    if(str.front() == '"') {
        if(str.back() == '"') {
            return true;
        }
    }
    return false;
}

instruction push(const std::variant<int, std::string>& value) {
    return {.opcode = PUSH, .value = value};
}

instruction dump() {
    return {.opcode = DUMP};
}

instruction parse_word_as_opcode(std::string word) {
    auto opcode_it = opcode_map.find(word);
    if(opcode_map.find(word) != opcode_map.end()) {
        return {.opcode = opcode_it->second};
    } else {
        try {
            const instruction op = {.opcode = PUSH, .value = stoi(word)};
            return op;
        } catch(const std::exception& e) {
            if(is_str_str(word)) { 
                word.erase(word.begin());
                word.erase(word.end() - 1);
                return {.opcode = PUSH, .value = word};
            } else {
                print_error("Unable to find a definition for \"", word, "\".");
                exit(1);
            }
        }
    }
}

program_t load_program(const std::string& filename) {
    std::ifstream file(filename);
    if(file.fail()) {
        print_error("Could not open file \"", filename, "\". Reason: ", termcolor::white<char>, strerror(errno), termcolor::reset<char>);
        exit(1);
    }
    
    program_t program;

    std::string words;
    std::getline(file, words);
    
    if(words.empty()) {
        exit(0);
    }
    
    std::regex pattern("(\"([^\"]*)\"|'([^']*)'|[^'\" ]+)");
    std::sregex_iterator iter(words.begin(), words.end(), pattern);
    std::sregex_iterator end;
    std::vector<std::string> split_parts;
    while(iter != end) {
        std::smatch match = *iter;
        split_parts.push_back(match.str());
        ++iter;
    }
    for(const auto& word : split_parts) {
        program.emplace_back(parse_word_as_opcode(word));
    }
    file.close();
    return program;
}

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
        } else if(std::holds_alternative<std::string>(elem)) {
            print<false>(std::cout, "\"", std::get<std::string>(elem), "\" ");
        }
    }
    print(std::cout, '\n');
}

void interpret_program(const program_t& program) {
    std::vector<std::variant<int, std::string>> stack;
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
                    }
                }
                break;
            }
            case DIV: {
                check_stack_size(stack);
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
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(stack.back())) {
                    print_error("Cannot compare strings.");
                    exit(1);
                }
                stack.push_back(std::get<int>(stack[stack.size() - 2]) < std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                break; 
            }
            case GT: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(stack.back())) {
                    print_error("Cannot compare strings.");
                    exit(1);
                }
                stack.push_back(std::get<int>(stack[stack.size() - 2]) > std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                break; 
            }
            case EQ: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(stack.back())) {
                    stack.push_back(std::get<std::string>(stack[stack.size() - 2]) == std::get<std::string>(stack[stack.size() - 1]) ? -1 : 0);
                } else if(std::holds_alternative<int>(stack.back())) {
                    stack.push_back(std::get<int>(stack[stack.size() - 2]) == std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                }
                break;
            }
            case NOT_EQ: {
                check_stack_size(stack);
                if(std::holds_alternative<std::string>(stack.back())) {
                    stack.push_back(std::get<std::string>(stack[stack.size() - 2]) != std::get<std::string>(stack[stack.size() - 1]) ? -1 : 0);
                } else if(std::holds_alternative<int>(stack.back())) {
                    stack.push_back(std::get<int>(stack[stack.size() - 2]) != std::get<int>(stack[stack.size() - 1]) ? -1 : 0);
                }
                break;
            }
            case DUMP: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<std::string>(stack.back())) {
                    print(std::cout, std::get<std::string>(stack.back()));
                } else if(std::holds_alternative<int>(stack.back())) {
                    print(std::cout, std::get<int>(stack.back()));
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
                check_stack_size(stack);
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
                check_stack_size(stack, 1);
                if(std::holds_alternative<std::string>(*(stack.end() - 1))) {
                    print_error("You cannot use emit with strings.");
                    exit(1);
                }
                auto a = std::get<int>(stack.back());
                stack.pop_back();
                break;
            }
            case EXIT: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    exit(std::get<int>(stack.back()));
                } else {
                    print_error("Invalid input parameter.");
                    exit(1);
                }
                break;
            }
            case SIZEOF: {
                check_stack_size(stack, 1);
                if(std::holds_alternative<int>(stack.back())) {
                    print(std::cout, sizeof(std::get<int>(stack.back())));
                } else if(std::holds_alternative<std::string>(stack.back())) {
                    print(std::cout, std::get<std::string>(stack.back()).size());
                }
            }
            case INC: {
                check_stack_size(stack, 1);
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

int main(int argc, char** argv) {
    if(argc < 2) {
        print_usage(argv[0]);
        print_error("No filename provided.");
        return 1;
    }

    interpret_program(load_program(argv[1]));
    return 0;
}