#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

class Lexer {
public:
    Lexer(const std::string& source) : source(source), position(0), line_count(1) {}

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
    size_t line_count;
};

#endif /* LEXER_HPP */