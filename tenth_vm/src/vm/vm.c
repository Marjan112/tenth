#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

/* helper functions */

static void check_stack(VM* vm, size_t offset);

void vm_init(VM* vm) {
    memset(&vm->program, 0, sizeof(vm->program));
    memset(vm->stack, 0, sizeof(vm->stack));
    vm->stack_top = vm->stack;
}

bool vm_load_program(VM* vm, const char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        fprintf(stderr, "[ERROR]: Could not read file \"%s\". Reason: %s\n", filename, strerror(errno));
        return false;
    }
    
    fread(&vm->program.inst_count, sizeof(vm->program.inst_count), 1, file);

    for(size_t i = 0; i < vm->program.inst_count; ++i) {
        Inst* inst = &vm->program.inst[i];
        fread(&inst->type, sizeof(inst->type), 1, file);
        if(inst->type == INST_PUSH) {
            fread(&inst->value.type, sizeof(inst->value.type), 1, file);
            if(inst->value.type == STACK_VALUE_INT) {
                fread(&inst->value.as_int64, sizeof(inst->value.as_int64), 1, file);
            } else if(inst->value.type == STACK_VALUE_FLOAT) {
                fread(&inst->value.as_float64, sizeof(inst->value.as_float64), 1, file);
            } else if(inst->value.type == STACK_VALUE_STR) {
                fread(&inst->value.as_str.count, sizeof(inst->value.as_str.count), 1, file);
                string_reserve(&inst->value.as_str, inst->value.as_str.count);
                fread(inst->value.as_str.data, inst->value.as_str.count, 1, file);
            }
        }
    }

    fclose(file);
    return true;
}

void vm_run(VM* vm) {
    while(vm->program.ip < vm->program.inst_count) {
        Inst inst = vm->program.inst[vm->program.ip];
        switch(inst.type) {
            case INST_PUSH: {
                vm_stack_push(vm, inst.value);
                ++vm->program.ip;
                break;
            }
            case INST_PLUS: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                Stack_Value c = stack_value_add(a, b);

                stack_value_free_if_str(a);
                stack_value_free_if_str(b);
                
                vm_stack_push(vm, c);

                ++vm->program.ip;
                break;
            }
            case INST_MINUS: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_sub(a, b));

                ++vm->program.ip;
                break;                
            }
            case INST_MUL: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_mul(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_DIV: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_div(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_LT: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_lt(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_GT: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_gt(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_LTEQ: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_lteq(a, b));
                
                ++vm->program.ip;
                break;
            }
            case INST_GTEQ: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_lteq(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_EQ: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_eq(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_NOT_EQ: {
                check_stack(vm, 2);

                Stack_Value b = vm_stack_pop(vm);
                Stack_Value a = vm_stack_pop(vm);
                vm_stack_push(vm, stack_value_not_eq(a, b));

                ++vm->program.ip;
                break;
            }
            case INST_DUMP: {
                check_stack(vm, 1);
                Stack_Value value = vm_stack_pop(vm);
                switch(value.type) {
                    case STACK_VALUE_STR: {
                        printf("%.*s\n", value.as_str.count, value.as_str.data);
                        string_free(&value.as_str);
                        break;
                    }
                    case STACK_VALUE_INT: {
                        printf("%ld\n", value.as_int64);
                        break;
                    }
                    case STACK_VALUE_FLOAT: {
                        printf("%lf\n", value.as_float64);
                        break;
                    }
                }
                ++vm->program.ip;
                break;
            }
            case INST_SHOW: {
                ++vm->program.ip;
                if(vm_is_stack_empty(vm)) {
                    printf("(empty)\n");
                    break;
                }
            
                for(Stack_Value* i = vm->stack; i < vm->stack_top; ++i) {
                    switch(i->type) {
                        case STACK_VALUE_INT: {
                            printf("%ld ", i->as_int64);
                            break;
                        }
                        case STACK_VALUE_FLOAT: {
                            printf("%lf ", i->as_float64);
                            break;
                        }
                        case STACK_VALUE_STR: {
                            printf("%.*s ", i->as_str.count, i->as_str.data);
                            break;
                        }
                    }
                }
                printf("\n");
                break;
            }
            case INST_DUP: {
                check_stack(vm, 1);

                Stack_Value value = vm_stack_back(vm);
                if(value.type == STACK_VALUE_STR) {
                    Stack_Value value_str_copy = {0};
                    value_str_copy.type = STACK_VALUE_STR;

                    string_copy(&value_str_copy.as_str, value.as_str);
                    vm_stack_push(vm, value_str_copy);
                } else vm_stack_push(vm, value);

                ++vm->program.ip;
                break;
            }
            case INST_DROP: {
                check_stack(vm, 1);
                stack_value_free_if_str(vm_stack_pop(vm));
                ++vm->program.ip;
                break;
            }
            case INST_SWAP: {
                check_stack(vm, 2);

                Stack_Value a = vm_stack_pop(vm);
                Stack_Value b = vm_stack_pop(vm);
                vm_stack_push(vm, a);
                vm_stack_push(vm, b);

                ++vm->program.ip;
                break;
            }
            case INST_OVER: {
                check_stack(vm, 2);
                vm_stack_push(vm, vm->stack[1]);
                ++vm->program.ip;
                break;
            }
            case INST_ROT: {
                check_stack(vm, 3);

                Stack_Value a = vm_stack_pop(vm);
                Stack_Value b = vm_stack_pop(vm);
                Stack_Value c = vm_stack_pop(vm);
                vm_stack_push(vm, b);
                vm_stack_push(vm, a);
                vm_stack_push(vm, c);
                
                ++vm->program.ip;
                break;
            }
            case INST_EXIT: {
                check_stack(vm, 1);
                
                Stack_Value value = vm_stack_pop(vm);
                if(value.type == STACK_VALUE_INT) {
                    exit(value.as_int64);
                } else {
                    fprintf(stderr, "[ERROR]: exit: invalid parameter, must be an integer");
                    exit(1);
                }

                ++vm->program.ip;
                break;
            }
            case INST_INC: {
                check_stack(vm, 1);

                Stack_Value* value = vm->stack_top - 1;
                if(value->type == STACK_VALUE_INT) {
                    ++value->as_int64;
                } else if(value->type == STACK_VALUE_FLOAT) {
                    ++value->as_float64;
                } else if(value->type == STACK_VALUE_STR) {
                    fprintf(stderr, "[ERROR]: inc: cannot use on strings");
                    exit(1);
                }
                
                ++vm->program.ip;
                break;
            }
            case INST_DEC: {
                check_stack(vm, 1);

                Stack_Value* value = vm->stack_top - 1;
                if(value->type == STACK_VALUE_INT) {
                    --value->as_int64;
                } else if(value->type == STACK_VALUE_FLOAT) {
                    --value->as_float64;
                } else if(value->type == STACK_VALUE_STR) {
                    fprintf(stderr, "[ERROR]: inc: cannot use on strings");
                    exit(1);
                }

                ++vm->program.ip;
                break;  
            }
            case INST_PRINT: {
                check_stack(vm, 1);

                String output = {0};

                for(Stack_Value* i = vm->stack; i < vm->stack_top; ++i) {
                    if(i->type == STACK_VALUE_INT) string_append_int64(&output, i->as_int64);
                    else if(i->type == STACK_VALUE_FLOAT) string_append_double(&output, i->as_float64);
                    else if(i->type == STACK_VALUE_STR) string_append_string(&output, i->as_str);
                }

                while(vm->stack_top > vm->stack) vm_stack_pop(vm);

                printf("%.*s", output.count, output.data);
                string_free(&output);

                ++vm->program.ip;
                break;
            }
            case INST_JMP: {
                check_stack(vm, 1);

                Stack_Value value = vm_stack_pop(vm);
                if(value.type == STACK_VALUE_INT) {
                    vm->program.ip = value.as_int64;
                } else {
                    fprintf(stderr, "[ERROR]: jmp: invalid parameter, must be an integer\n");
                    exit(1);
                }
                break;
            }
        }
    }
}

bool vm_is_stack_empty(VM* vm) {
    return vm->stack_top == vm->stack;
}

void vm_stack_push(VM* vm, Stack_Value value) {
    if(vm->stack_top > vm->stack + STACK_SIZE) {
        fprintf(stderr, "[ERROR]: Stack overflow!\n");
        abort();
    }
    *vm->stack_top++ = value;
}

Stack_Value* vm_stack_pop_top(VM* vm) {
    if(vm->stack_top == vm->stack) {
        fprintf(stderr, "[ERROR]: Stack underflow!\n");
        abort();
    }
    return --vm->stack_top;
}

Stack_Value vm_stack_pop(VM* vm) {
    return *vm_stack_pop_top(vm);
}

Stack_Value vm_stack_back(VM* vm) {
    return *(vm->stack_top - 1);
}

static void check_stack(VM* vm, size_t offset) {
    if(vm->stack_top - offset < vm->stack) {
        fprintf(stderr, "[ERROR]: Stack underflow!\n");
        abort();
    } else if(vm->stack_top > vm->stack + STACK_SIZE) {
        fprintf(stderr, "[ERROR]: Stack overflow!\n");
        abort();
    }
}