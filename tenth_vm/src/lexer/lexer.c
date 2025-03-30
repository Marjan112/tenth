#include "lexer.h"

#include <string.h>
#include <ctype.h>
#include <assert.h>

/* helper functions */

static void skip_whitespace(Lexer* lexer);
static void read_string(Lexer* lexer, String* token);
static void read_number(Lexer* lexer, String* token);
static void read_word(Lexer* lexer, String* token);

bool lexer_read_entire_file(Lexer* lexer, const char* filename) {
    return string_read_entire_file(&lexer->source, filename);
}

bool lexer_get_next_token(Lexer* lexer, String* token) {
    string_reset(token);
    skip_whitespace(lexer);

    if(lexer->position >= lexer->source.count) return false;

    char current_char = lexer->source.data[lexer->position];
    if(current_char == '"') {
        read_string(lexer, token);
        return true;
    }
    if(isdigit(current_char) || current_char == '-') {
        read_number(lexer, token);
        return true;
    }
    
    read_word(lexer, token);
    return true;
}

void lexer_free(Lexer* lexer) {
    string_free(&lexer->source);
    memset(lexer, 0, sizeof(Lexer));
}

static void skip_whitespace(Lexer* lexer) {
    while(lexer->position < lexer->source.count && isspace(lexer->source.data[lexer->position])) {
        ++lexer->position;
    }
}

static void read_string(Lexer* lexer, String* token) {
    string_append_char(token, lexer->source.data[lexer->position++]);
    while(lexer->position < lexer->source.count && lexer->source.data[lexer->position] != '"') {
        if(lexer->source.data[lexer->position] == '\\') {
            if(lexer->source.data[lexer->position + 1] == 'n') {
                string_erase_char(&lexer->source, lexer->position);
                string_erase_char(&lexer->source, lexer->position - 1);
                string_insert_char(&lexer->source, lexer->position, '\n');
            }
        }
        string_append_char(token, lexer->source.data[lexer->position++]);
    }
    string_append_char(token, lexer->source.data[lexer->position++]);
}

static void read_number(Lexer* lexer, String* token) {
    string_append_char(token, lexer->source.data[lexer->position++]);
    while(lexer->position < lexer->source.count && (isdigit(lexer->source.data[lexer->position]) || lexer->source.data[lexer->position] == '.')) {
        string_append_char(token, lexer->source.data[lexer->position++]);
    }
}

static void read_word(Lexer* lexer, String* token) {
    string_append_char(token, lexer->source.data[lexer->position++]);
    while(lexer->position < lexer->source.count && !isspace(lexer->source.data[lexer->position])) {
        string_append_char(token, lexer->source.data[lexer->position++]);
    }
}