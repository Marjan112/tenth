#pragma once

#include "../program.h"
#include "../stack/stack.h"

#define STACK_SIZE 128

typedef struct {
    Program program;
    Stack_Value stack[STACK_SIZE];
    Stack_Value* stack_top;
} VM;

void vm_init(VM* vm);
bool vm_load_program(VM* vm, const char* filename);
void vm_run(VM* vm);
bool vm_is_stack_empty(VM* vm);
void vm_stack_push(VM* vm, Stack_Value value);
Stack_Value* vm_stack_pop_top(VM* vm);
Stack_Value vm_stack_pop(VM* vm);
Stack_Value vm_stack_back(VM* vm);