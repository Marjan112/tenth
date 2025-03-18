# Tenth

This project is using [termcolor](https://github.com/ikalnytskyi/termcolor) library.

# Building

Install:
* [cmake](https://cmake.org/)
* GCC *if you are on Linux*
* [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) *if you are on Windows*
  
``` console
$ mkdir build
$ cd build
$ cmake ../
```

On Linux:
``` console
$ make
```
On Windows:
``` console
$ msbuild 10th.sln
```

# Examples:

## Push

To push a number onto the stack, you need to type:

    10
## Addition

If you want to add some numbers:

    10 15 +

If you want to print the result and pop the top of the stack:

    10 15 + .

## Dump

To dump value from the stack

    420 . (420 gets dumped)
    420 69 . (69 gets dumped)

## Show

To show stack:

    10 25 42 88 90 show

## Multiplication

For example, this expression: 2 + 2 * 2 can be written like this:

    2 2 * 2 + .

or some other expression like 2 - 2 * 2  - 2 can be written like this:

    -2 2 * 2 -2 - .

## Division

To divide a number:

    1.0 2.0 / .

## Comparison

To compare two numbers:

5 is less than 10

    5 10 < .

This is going to be true, so the value thats going to be pushed onto stack is -1 representing true.

10 is greater than 50

    10 50 > .

This is going to be false, so the value that's going to be pushed onto stack is 0 representing false.

50 is equal to 50

    50 50 = .

## Duplication

To duplicate top value onto stack, you need to have some other value onto stack to be able to duplicate it:

    15 dup show

the result will be 
    
    15 15

## Drop

Droping is almost same as dumping, but you are not printing the value that you've poped from the top of the stack. To drop a value you need to have one already:

    10 show drop show

First we are going to push 10 and show the stack. Second we are going to call opcode drop, and then we are going to show stack again.

Result is going to be:

    10
    (empty)

## Swap

In order to swap two values, we need to push them to stack.

    10 20 show swap show

Result is going to be:

    10 20
    20 10

## Over

Over is not as obvious as the other opcodes. It duplicates second element to the top of the stack. Like this:

    420 69 56 show
    over show

Result is:

    420 69 56
    420 69 56 69

## Rot

Rot opcode is going to rotate first three elements onto stack. The third element from the top of the stack gets moved to the top of the stack, pushing the other two elements down.

    1 2 3 show
    rot show

Result:

    2 3 1

## Emit

Emit opcode is going to print ascii character.
Like this:

    65 emit

is going to print 'a'.

## Exit

Exit is opcode that is going to terminate program with exit code.
Like this:

    0 exit

Result is 4

## Increment & Decrement

To increment top of the stack:

    15 inc .

If you want do decrement:
    
    15 dec .

## String literals

    "Hello, World!" .

This is going to dump Hello, World! in the console.

## Print

To print something that is on the stack, you need to do this:

    "Hello, " 123 " " 123.5 " World\n" print

This is going to print Hello, 123 123.5 World.

# License
Licensed under the MIT License, see the [LICENSE](./LICENSE) file.

See the [termcolor license](./src/termcolor/LICENSE).
