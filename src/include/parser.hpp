#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <cstring>
#include <variant>
#include <regex>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    namespace __internal {
        bool is_str_str(const std::string& str) {
            if(str.front() == '"') {
                if(str.back() == '"') {
                    return true;
                }
            }
            return false;
        }

        namespace __test {
            instruction push(const std::variant<int, std::string>& value) {
                return {.opcode = PUSH, .value = value};
            }

            instruction dump() {
                return {.opcode = DUMP};
            }
        }
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
                if(__internal::is_str_str(word)) { 
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

    
}

#endif /* PARSER_HPP */