#include <stdio.h>

#include "vm/vm.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("[USAGE]: %s <program>\n", argv[0]);
        return 1;
    }

    VM vm;
    vm_init(&vm);
    if(!vm_load_program(&vm, argv[1])) return 1;
    vm_run(&vm);
    return 0;
}