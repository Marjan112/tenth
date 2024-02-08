#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <variant>
#include <regex>
#include <sstream>

#include "opcodes.hpp"
#include "print.hpp"

namespace tenth {
    class Lexer {
    public:
        Lexer(const std::string& source) : source(source), position(0) {}

        std::string get_next_token() {
            skip_whitespace();

            if(position >= source.length()) {
                return "";
            }

            char current_char = source[position];
            if(current_char == '"') {
                return read_string();
            } else if(isdigit(current_char) || current_char == '-') {
                return read_number();
            } else {
                return read_word();
            }
        }

    private:
        void skip_whitespace() {
            while(position < source.length() && std::isspace(source[position])) {
                position++;
            }
        }

        std::string read_string() {
            size_t start = position++;
            while(position < source.length() && source[position] != '"') {
                position++;
            }
            position++;
            return source.substr(start, position - start);
        }

        std::string read_number() {
            size_t start = position++;
            while(position < source.length() && (isdigit(source[position]) || source[position] == '.')) {
                position++;
            }
            return source.substr(start, position - start);
        }

        std::string read_word() {
            size_t start = position++;
            while(position < source.length() && !std::isspace(source[position])) {
                position++;
            }
            return source.substr(start, position - start);
        }

        std::string source;
        size_t position;
    };

    class Parser {
    public:
        Parser(const std::string& filename) : filename(filename) {}

        program_t parse() {
            std::ifstream file(filename);
            if(file.fail()) {
                print_error("Could not open file \"", filename, "\". Reason: ", termcolor::white<char>, strerror(errno), termcolor::reset<char>);
                exit(1);
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            Lexer lexer(buffer.str());
            std::string token;
            program_t program;

            while(!(token = lexer.get_next_token()).empty()) {
                program.emplace_back(parse_token(token));
            }

            return program;
        }
    private:
        instruction parse_token(std::string token) {
            auto word_it = BUILTIN_WORDS.find(token);
            if(word_it != BUILTIN_WORDS.end()) {
                return {.opcode = word_it->second};
            }
            if(is_int(token)) {
                return {.opcode = PUSH, .value = stoi(token)};
            } else if(is_str(token)) {
                token.erase(token.begin());
                token.erase(token.end() - 1);
                return {.opcode = PUSH, .value = token};
            } else if(is_float(token)) {
                return {.opcode = PUSH, .value = stof(token)};
            } else {
                print_error("Unable to find a definition for \"", token, "\".");
                exit(1);
            }
        }

        bool is_int(const std::string& token) {
            if(token.empty()) {
                return false;
            }

            size_t pos;
            try {
                std::stoi(token, &pos);
                return pos == token.length();
            } catch(...) {
                return false;
            }
        }

        bool is_float(const std::string& token) {
            if(token.empty()) {
                return false;
            }

            size_t pos;
            try {
                std::stof(token, &pos);
                return pos == token.length();
            } catch(...) {
                return false;
            }
        }

        bool is_str(const std::string& token) {
            if(token.empty()) {
                return false;
            }

            return !token.empty() && token.front() == '"' && token.back() == '"';
        }

        std::string filename;
    };
};

#endif /* PARSER_HPP */