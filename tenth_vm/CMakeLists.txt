cmake_minimum_required(VERSION 3.25.1)
project(tenth)
set(CMAKE_C_STANDARD 23)

add_executable(tc
    src/tc.c
    src/parser/parser.c
    src/string/string.c
    src/lexer/lexer.c)
add_executable(tvm 
    src/tvm.c
    src/string/string.c
    src/stack/stack.c
    src/vm/vm.c)