#include <stdio.h>

#include "parser/parser.h"

bool compile(const char* inputfile, const char* outputfile) {
    Program program = {0};
    if(!parse_file(inputfile, &program)) return false;
    
    FILE* file = fopen(outputfile, "w");
    if(file == NULL) return false;

    fwrite(&program.inst_count, sizeof(program.inst_count), 1, file);

    for(size_t i = 0; i < program.inst_count; ++i) {
        Inst inst = program.inst[i];
        fwrite(&inst.type, sizeof(inst.type), 1, file);
        if(inst.type == INST_PUSH) {
            fwrite(&inst.value.type, sizeof(inst.value.type), 1, file);
            if(inst.value.type == STACK_VALUE_INT) {
                fwrite(&inst.value.as_int64, sizeof(inst.value.as_int64), 1, file);
            } else if(inst.value.type == STACK_VALUE_FLOAT) {
                fwrite(&inst.value.as_float64, sizeof(inst.value.as_float64), 1, file);
            } else if(inst.value.type == STACK_VALUE_STR) {
                fwrite(&inst.value.as_str.count, sizeof(inst.value.as_str.count), 1, file);
                fwrite(inst.value.as_str.data, inst.value.as_str.count, 1, file);
                string_free(&inst.value.as_str);
            }
        }
    }

    fclose(file);
    return true;
}

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("[USAGE]: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    return !compile(argv[1], argv[2]);
}