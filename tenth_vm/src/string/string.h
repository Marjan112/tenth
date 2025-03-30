#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_STRING_CAPACITY 256

typedef struct {
    char* data;
    size_t count;
    size_t capacity;
} String;

void string_reserve(String* string, size_t reserve);

void string_append_char(String* string, char ch);
void string_append_cstr_size(String* string, const char* cstr, size_t cstr_len);
void string_append_cstr(String* string, const char* cstr);
void string_append_string(String* string, String other_string);
void string_append_null(String* string);
void string_append_int64(String* string, int64_t value);
void string_append_double(String* string, double value);

void string_insert_char(String* string, size_t index, char ch);
void string_insert_cstr_size(String* string, size_t index, const char* cstr, size_t cstr_len);
void string_insert_cstr(String* string, size_t index, const char* cstr);
void string_insert_string(String* string, size_t index, String other_string);

void string_erase_char(String* string, size_t index);

void string_copy(String* string, String other);

bool string_read_entire_file(String* string, const char* filename);

bool string_is_empty(String string);

int64_t string_to_int64(String string);
double string_to_double(String string);

bool string_equal_cstr(String string, const char* cstr);
bool string_equal_string(String a, String b);

void string_reverse(String* string);

String int64_to_string(int64_t value);
String double_to_string(double value);

void string_reset(String* string);
void string_free(String* string);