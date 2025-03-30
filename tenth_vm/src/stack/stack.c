#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void stack_value_free_if_str(Stack_Value value) {
    if(value.type == STACK_VALUE_STR) string_free(&value.as_str);
}

Stack_Value stack_value_not(Stack_Value value) {
    if(value.type != STACK_VALUE_STR) {
        return (Stack_Value) {
            .type = value.type,
            .as_int64 = !value.as_int64
        };
    }

    fprintf(stderr, "[ERROR]: Cant logically negate types that are not numbers.\n");
    exit(1);
}

Stack_Value stack_value_add(Stack_Value a, Stack_Value b) {
    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 + b.as_int64
            }; 
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 + b.as_float64
            };
        } else if(a.type == STACK_VALUE_STR) {
            Stack_Value c = {0};
            c.type = STACK_VALUE_STR;
            string_append_string(&c.as_str, a.as_str);
            string_append_int64(&c.as_str, b.as_int64);
            return c;
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 + b.as_float64,
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_int64 + b.as_float64,
            };
        } else if(a.type == STACK_VALUE_STR) {
            Stack_Value c = {0};
            c.type = STACK_VALUE_STR;
            string_append_string(&c.as_str, a.as_str);
            string_append_double(&c.as_str, b.as_float64);
            return c;
        }
    } else if(b.type == STACK_VALUE_STR) {
        Stack_Value c = {0};
        c.type = STACK_VALUE_STR;
        if(a.type == STACK_VALUE_STR) string_append_string(&c.as_str, a.as_str);
        else if(a.type == STACK_VALUE_INT) string_append_int64(&c.as_str, a.as_int64);
        else if(a.type == STACK_VALUE_FLOAT) string_append_double(&c.as_str, a.as_float64);
        string_append_string(&c.as_str, b.as_str);
        return c;
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_sub(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Cant use minus on strings.\n");
        exit(1);
    }

    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 - b.as_int64
            }; 
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 - b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 - b.as_float64,
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_int64 - b.as_float64,
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_mul(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Multiplying strings is not supported yet.\n");
        exit(1);
    }

    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 * b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 * b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 * b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_int64 * b.as_float64
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_div(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Cant divide with strings.\n");
        exit(1);
    }

    if(b.as_int64 == 0) {
        fprintf(stderr, "[ERROR]: Cant divide by zero.\n");
        exit(1);
    }

    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 / b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 / b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_float64 / b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_FLOAT,
                .as_float64 = a.as_int64 / b.as_float64
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_lt(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Cant use '<' or '>' on strings.\n");
        exit(1);
    }

    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 < b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 < b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 < b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 < b.as_float64
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_gt(Stack_Value a, Stack_Value b) {
    return stack_value_not(stack_value_lt(a, b));
}

Stack_Value stack_value_lteq(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Cant use '<=' on strings.\n");
        exit(1);
    }
    
    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 <= b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 <= b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 <= b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 <= b.as_float64
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_gteq(Stack_Value a, Stack_Value b) {
    if(a.type == STACK_VALUE_STR || b.type == STACK_VALUE_STR) {
        fprintf(stderr, "[ERROR]: Cant use '>=' on strings.\n");
        exit(1);
    }
    
    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 >= b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 >= b.as_int64
            };
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 >= b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 >= b.as_float64
            };
        }
    }

    return (Stack_Value){0};
}

Stack_Value stack_value_eq(Stack_Value a, Stack_Value b) {
    if(b.type == STACK_VALUE_INT) {
        if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 == b.as_int64
            };
        } else if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 == b.as_int64
            };
        } else if(a.type == STACK_VALUE_STR) {
            fprintf(stderr, "[ERROR]: Cant use '=' on strings and numbers.\n");
            exit(1);
        }
    } else if(b.type == STACK_VALUE_FLOAT) {
        if(a.type == STACK_VALUE_FLOAT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_float64 == b.as_float64
            };
        } else if(a.type == STACK_VALUE_INT) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = a.as_int64 == b.as_float64
            };
        } else if(a.type == STACK_VALUE_STR) {
            fprintf(stderr, "[ERROR]: Cant use '=' on strings and numbers.\n");
            exit(1);
        }
    } else if(b.type == STACK_VALUE_STR) {
        if(a.type == STACK_VALUE_STR) {
            return (Stack_Value) {
                .type = STACK_VALUE_INT,
                .as_int64 = string_equal_string(a.as_str, b.as_str)
            };
        } else if(a.type == STACK_VALUE_FLOAT || a.type == STACK_VALUE_INT) {
            fprintf(stderr, "[ERROR]: Cant use '=' on strings and numbers.\n");
            exit(1);
        }
    }
    
    return (Stack_Value){0};
}

Stack_Value stack_value_not_eq(Stack_Value a, Stack_Value b) {
    return stack_value_not(stack_value_eq(a, b));
}