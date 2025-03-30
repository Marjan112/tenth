#include "parser.h"
#include "../lexer/lexer.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct {
    const char* key;
    Inst_Type value;
} Inst_Pair;

const Inst_Pair inst_map[] = {
    {.key = "+", .value = INST_PLUS},
    {.key = "-", .value = INST_MINUS},
    {.key = "*", .value = INST_MUL},
    {.key = "/", .value = INST_DIV},
    {.key = "<", .value = INST_LT},
    {.key = ">", .value = INST_GT},
    {.key = "<=", .value = INST_LTEQ},
    {.key = ">=", .value = INST_GTEQ},
    {.key = "==", .value = INST_EQ},
    {.key = "!=", .value = INST_NOT_EQ},
    {.key = ".", .value = INST_DUMP},
    {.key = "show", .value = INST_SHOW},
    {.key = "dup", .value = INST_DUP},
    {.key = "drop", .value = INST_DROP},
    {.key = "swap", .value = INST_SWAP},
    {.key = "over", .value = INST_OVER},
    {.key = "rot", .value = INST_ROT},
    {.key = "exit", .value = INST_EXIT},
    {.key = "inc", .value = INST_INC},
    {.key = "dec", .value = INST_DEC},
    {.key = "print", .value = INST_PRINT},
    {.key = "jmp", .value = INST_JMP}
};
const size_t inst_map_count = sizeof(inst_map) / sizeof(inst_map[0]);

/* helper functions */

static ssize_t find_inst_pair(String key);
static Inst parse_token(String token);
static bool is_int(String token);
static bool is_str(String token);
static bool is_float(String token);

bool parse_file(const char* filename, Program* program) {
    Lexer lexer = {0};
    if(!lexer_read_entire_file(&lexer, filename)) return false;

    String token = {0};
    size_t ip = 0;
    while(lexer_get_next_token(&lexer, &token)) {
        program->inst[ip] = parse_token(token);
        if(program->inst[ip].type == INST_) {
            fprintf(stderr, "[ERROR]: (in %s) Unable to find definition for '%.*s'.\n", filename, token.count, token.data);
            lexer_free(&lexer);
            string_free(&token);
            return false;
        }
        
        ++ip;
        ++program->inst_count;
    }

    lexer_free(&lexer);
    string_free(&token);
    return true;
}

static ssize_t find_inst_pair(String key) {
    for(ssize_t i = 0; i < inst_map_count; ++i) if(string_equal_cstr(key, inst_map[i].key)) return i;
    return -1;
}

static Inst parse_token(String token) {
    ssize_t inst_pair_index = find_inst_pair(token);
    if(inst_pair_index != -1) {
        return (Inst) {
            .type = inst_map[inst_pair_index].value,
            .value = STACK_VALUE_NO_VALUE
        };
    }

    if(is_int(token)) {
        return (Inst) {
            .type = INST_PUSH,
            .value = (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = string_to_int64(token)
            }
        };
    }
    if(is_str(token)) {
        String value = {0};
        for(int i = 0; i < token.count; ++i) {
            if(i > token.count - 1) break;
            if(token.data[i + 1] == '"') break;
            string_append_char(&value, token.data[i + 1]);
        }

        return (Inst) {
            .type = INST_PUSH,
            .value = (Stack_Value) {
                .type = STACK_VALUE_STR,
                .as_str = value
            }
        };
    }
    if(is_float(token)) {
        return (Inst) {
            .type = INST_PUSH,
            .value = (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = string_to_double(token)
            }
        };
    }

    return (Inst){.type = INST_};
}

static bool is_int(String token) {
    if(string_is_empty(token)) {
        return false;
    }

    size_t index = 0;

    String token_copy = {0};
    string_copy(&token_copy, token);
    string_append_null(&token_copy);

    if(token_copy.data[index] == '-') ++index;

    bool result = (index < token_copy.count - 1) && (strspn(token_copy.data + index, "0123456789") == token_copy.count - 1 - index);
    string_free(&token_copy);
    return result;
}

static bool is_str(String token) {
    return !string_is_empty(token) && token.data[0] == '"' && token.data[token.count - 1] == '"';
}

static bool is_float(String token) {
    if(string_is_empty(token)) {
        return false;
    }

    size_t index = 0;

    if(token.data[0] == '-') ++index;

    bool has_digit = false;
    bool has_dot = false;

    for(; index < token.count; ++index) {
        if(isdigit(token.data[index])) {
            has_digit = true;
        } else if(token.data[index] == '.' && !has_dot) {
            has_dot = true;
        } else {
            return false;
        }
    }

    return has_digit;
}