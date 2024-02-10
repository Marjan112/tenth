#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <sstream>
#include <cstring>

#include "opcodes.hpp"
#include "print.hpp"
#include "Lexer.hpp"

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

#endif /* PARSER_HPP */