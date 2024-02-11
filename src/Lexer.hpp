#pragma once

#include <string>

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
            if(source[position] == '\\') {
                switch(source[position + 1]) {
                    case 'e': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\e');
                        break;
                    }
                    case 'r': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\r');
                        break;
                    }
                    case 't': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\t');
                        break;
                    }
                    case 'a': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\a');
                        break;
                    }
                    case 'f': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\f');
                        break;
                    }
                    case 'v': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\v');
                        break;
                    }
                    case 'b': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\b');
                        break;
                    }
                    case 'n': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\n');
                        break;
                    }
                    case '\\': {
                        source.erase(source.begin() + position, source.begin() + position + 2);
                        source.insert(source.begin() + position, '\\');
                        break;
                    };
                    default: {
                        print_error("Unknown escape sequence.");
                        exit(1);
                        break;
                    }
                }
            }
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