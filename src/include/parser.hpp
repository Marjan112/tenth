#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <variant>
#include <regex>
#include <sstream>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    namespace __internal {
        bool is_word_str(const std::string& word) {
            return word.front() == '"' && word.back() == '"';
        }

        bool is_word_int(const std::string& word) {
            int start_index = 0;

            if(word.front() == '-') {
                if(word.length() == 1) {
                    return false;
                }
                start_index = 1;
            }

            for(int i = start_index; i < word.length(); i++) {
                if(!isdigit(word[i])) {
                    return false;
                }
            }

            return true;
        }

        bool is_word_float(const std::string& word) {
            if(word.empty()) {
                return false;
            }

            int start_index = 0;

            if(word.front() == '-') {
                if(word.length() == 1) {
                    return false;
                }
                start_index = 1;
            }

            bool decimal_point = false;

            for(int i = start_index; i < word.length(); i++) {
                if(word[i] == '.') {
                    if(decimal_point == true) {
                        return false;
                    }
                    decimal_point = true;
                } else if(!isdigit(word[i])) {
                    return false;
                }
            }
            
            return true;
        }

        namespace __test {
            instruction push(const stack_value_t& value) {
                return {.opcode = PUSH, .value = value};
            }

            instruction plus() {
                return {.opcode = PLUS};
            }

            instruction dump() {
                return {.opcode = DUMP};
            }
        }
    }

    instruction parse_word_as_opcode(std::string word) {
        auto word_it = BUILTIN_WORDS.find(word);
        if(word_it != BUILTIN_WORDS.end()) {
            return {.opcode = word_it->second};
        } else {
            if(__internal::is_word_int(word)) {
                return {.opcode = PUSH, .value = stoi(word)};
            } else if(__internal::is_word_str(word)) {
                word.erase(word.begin());
                word.erase(word.end() - 1);
                return {.opcode = PUSH, .value = word};
            } else if(__internal::is_word_float(word)) {
                return {.opcode = PUSH, .value = stof(word)};
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

        std::string whole_file;
        std::string source;

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        whole_file = ss.str();

        if(whole_file.empty()) {
            return {};
        }

        for(const auto& ch : whole_file) {
            if(ch == '\n') {
                source += ' ';
            } else {
                source += ch;
            }
        }
        
        std::regex pattern("(\"([^\"]*)\"|'([^']*)'|[^'\" ]+)");

        std::sregex_iterator iter(source.begin(), source.end(), pattern);
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
        return program;
    }
}

#endif /* PARSER_HPP */