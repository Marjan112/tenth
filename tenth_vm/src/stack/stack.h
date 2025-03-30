#pragma once

#include "../string/string.h"

#include <stdint.h>

typedef enum {
    STACK_VALUE_NO_VALUE,
    STACK_VALUE_INT,
    STACK_VALUE_FLOAT,
    STACK_VALUE_STR
} Stack_Value_Type;

typedef struct {
    Stack_Value_Type type;
    union {
        int64_t as_int64;
        double as_float64;
        String as_str;
    };
} Stack_Value;

void stack_value_free_if_str(Stack_Value value);

Stack_Value stack_value_not(Stack_Value value);

Stack_Value stack_value_add(Stack_Value a, Stack_Value b);
Stack_Value stack_value_sub(Stack_Value a, Stack_Value b);
Stack_Value stack_value_mul(Stack_Value a, Stack_Value b);
Stack_Value stack_value_div(Stack_Value a, Stack_Value b);
Stack_Value stack_value_lt(Stack_Value a, Stack_Value b);
Stack_Value stack_value_gt(Stack_Value a, Stack_Value b);
Stack_Value stack_value_lteq(Stack_Value a, Stack_Value b);
Stack_Value stack_value_gteq(Stack_Value a, Stack_Value b);
Stack_Value stack_value_eq(Stack_Value a, Stack_Value b);
Stack_Value stack_value_not_eq(Stack_Value a, Stack_Value b);