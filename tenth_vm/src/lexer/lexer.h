#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "../string/string.h"

typedef struct {
    String source;
    size_t position;
} Lexer;

bool lexer_read_entire_file(Lexer* lexer, const char* filename);
bool lexer_get_next_token(Lexer* lexer, String* token);
void lexer_free(Lexer* lexer);