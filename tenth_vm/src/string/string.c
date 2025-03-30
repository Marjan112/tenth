#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

void string_reserve(String* string, size_t reserve) {
    if(reserve > string->capacity) {
        string->capacity += reserve;
        string->data = realloc(string->data, string->capacity);
        assert(string->data != NULL);
    }
}

void string_append_char(String* string, char ch) {
    if(string->count >= string->capacity) {
        string->capacity = string->capacity == 0 ? DEFAULT_STRING_CAPACITY : string->capacity * 2;
        string->data = realloc(string->data, string->capacity);
        assert(string->data != NULL);
    }

    string->data[string->count++] = ch;
}

void string_append_cstr_size(String* string, const char* cstr, size_t cstr_len) {
    if(string->count >= string->capacity) {
        string->capacity = string->capacity == 0 ? DEFAULT_STRING_CAPACITY : string->capacity * 2;
        string->data = realloc(string->data, string->capacity);
        assert(string->data != NULL);
    }
    
    for(int i = 0; i < cstr_len; ++i) {
        string->data[string->count++] = cstr[i];
    }
}

void string_append_cstr(String* string, const char* cstr) {
    string_append_cstr_size(string, cstr, strlen(cstr));
}

void string_append_string(String* string, String other_string) {
    string_append_cstr_size(string, other_string.data, other_string.count);
}

void string_append_null(String* string) {
    string_append_char(string, '\0');
}

void string_append_int64(String* string, int64_t value) {
    String string_value = int64_to_string(value);
    string_append_string(string, string_value);
    string_free(&string_value);
}

void string_append_double(String* string, double value) {
    String string_value = double_to_string(value);
    string_append_string(string, string_value);
    string_free(&string_value);
}

void string_insert_char(String *string, size_t index, char ch) {
    assert(index < string->count);

    if(string->count >= string->capacity) {
        string->capacity = string->capacity == 0 ? 1 : string->capacity * 2;
        string->data = (char*)realloc(string->data, string->capacity);
        assert(string->data != NULL);
    }

    for(size_t i = string->count; i > index; --i) {
        string->data[i] = string->data[i - 1];
    }

    string->data[index] = ch;
    ++string->count;
}

void string_insert_cstr_size(String *string, size_t index, const char *cstr, size_t cstr_len) {
    assert(index < string->count);

    if(string->count + cstr_len >= string->capacity) {
        string->capacity = string->capacity == 0 ? cstr_len : string->capacity * 2;
        string->data = (char*)realloc(string->data, string->capacity);
        assert(string->data != NULL);
    }

    for(size_t i = string->count; i > index; --i) {
        string->data[i + cstr_len - 1] = string->data[i - 1];
    }

    memcpy(&string->data[index], cstr, cstr_len);
    
    string->count += cstr_len;
}

void string_insert_cstr(String* string, size_t index, const char* cstr) {
    string_insert_cstr_size(string, index, cstr, strlen(cstr));
}

void string_insert_string(String* string, size_t index, String other_string) {
    string_insert_cstr_size(string, index, other_string.data, other_string.count);
}

void string_erase_char(String* string, size_t index) {
    assert(index < string->count);

    for(size_t i = 0, j = 0; i < string->count; ++i) {
        if(i != index) {
            string->data[j++] = string->data[i];
        }
    }

    --string->count;
}

void string_copy(String* string, String other) {
    string->capacity = other.capacity;
    string->count = other.count;
    string->data = (char*)malloc(string->capacity);
    assert(string->data != NULL);
    memcpy(string->data, other.data, string->count);
}

// Implementation stolen from https://github.com/tsoding/nob.h/blob/main/nob.h - nob_read_entire_file
bool string_read_entire_file(String* string, const char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: %s\n", filename, strerror(errno));
        return false;
    }

    if(fseek(file, 0, SEEK_END) < 0) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: %s\n", filename, strerror(errno));
        fclose(file);
        return false;
    }

    size_t m = ftell(file);
    if(m < 0) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: %s\n", filename, strerror(errno));
        fclose(file);
        return false;
    }

    if(fseek(file, 0, SEEK_SET) < 0) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: %s\n", filename, strerror(errno));
        fclose(file);
        return false;
    }

    size_t new_count = string->count + m;
    if(new_count >= string->capacity) {
        string->data = realloc(string->data, new_count);
        assert(string->data != NULL);
        string->capacity = new_count;
    }

    fread(string->data + string->count, m, 1, file);
    if(ferror(file)) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: Unknown\n", filename);
        fclose(file);
        return false;
    }

    string->count = new_count;

    fclose(file);
    return true;
}

bool string_is_empty(String string) {
    return string.count == 0;
}

int64_t string_to_int64(String string) {
    String str_copy = {0};
    string_copy(&str_copy, string);
    string_append_null(&str_copy);

    long num = strtol(str_copy.data, NULL, 10);
    string_free(&str_copy);
    return num;
}

double string_to_double(String string) {
    String str_copy = {0};
    string_copy(&str_copy, string);
    string_append_null(&str_copy);

    double num = strtod(str_copy.data, NULL);
    string_free(&str_copy);
    return num;
}

bool string_equal_cstr(String string, const char* cstr) {
    if(string.count != strlen(cstr)) return false;
    return !strncmp(string.data, cstr, string.count);
}

bool string_equal_string(String a, String b) {
    if(a.count != b.count) return false;
    return !strncmp(a.data, b.data, a.count);
}

void string_reverse(String* string) {
    for(int i = 0, j = string->count - 1; i < j; ++i, --j) {
        char t = string->data[i];
        string->data[i] = string->data[j];
        string->data[j] = t;
    }
}

String int64_to_string(int64_t value) {
    String result = {0};
    string_reserve(&result, DEFAULT_STRING_CAPACITY);

    result.count = sprintf(result.data, "%ld", value);
    return result;
}

String double_to_string(double value) {
    String result = {0};
    string_reserve(&result, DEFAULT_STRING_CAPACITY);

    result.count = sprintf(result.data, "%lf", value);
    return result;
}

void string_reset(String* string) {
    memset(string->data, 0, string->capacity);
    string->count = 0;
}

void string_free(String* string) {
    free(string->data);   
    memset(string, 0, sizeof(String));
}