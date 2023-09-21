#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <cstring>
#include <variant>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    namespace __internal {
        bool is_str_int(const std::string& str) {
            for(const auto& ch : str) {
                if(std::isdigit(ch) == 0) {
                    return false;
                }
            }
            return true;
        }

        bool is_str_str(const std::string& str) {
            if(str.front() == '"') {
                if(str.back() == '"') {
                    return true;
                }
            }
            return false;
        }

        namespace __test {
            instruction push(std::variant<long long, std::string> value) {
                if(std::holds_alternative<long long>(value)) {
                    return {.opcode = PUSH, .longlong_value = std::get<long long>(value), .token_type = INT};
                } else if(std::holds_alternative<std::string>(value)) {
                    return {.opcode = PUSH, .string_value = std::get<std::string>(value), .token_type = STR};
                }
                return {};
            }

            instruction dump() {
                return {.opcode = DUMP, .token_type = WORD};
            }
        }
    }

    instruction parse_word_as_opcode(const std::string& word) {
        auto it = opcode_map.find(word);
        if(it != opcode_map.end()) {
            return {.opcode = it->second, .token_type = WORD};
        } else {
            if(__internal::is_str_int(word)) {
                return {.opcode = PUSH, .longlong_value = stoll(word), .token_type = INT};
            } else {
                print_error("Unable to find a definition for \"", word, "\".");
                exit(1);
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

        std::string word;

        while(file >> word) {
            if(word.front() == '"') {
                UNIMPLEMENTED("String literals arent implemented yet.");
            } else {
                program.emplace_back(parse_word_as_opcode(word));
            }
        }

        file.close();
        return program;
    }
}

#endif /* PARSER_HPP */