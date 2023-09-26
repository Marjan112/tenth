# The Programming Language "Tenth"

I got bored, so I created a programming language similar to Forth called Tenth.
By the way you should check out <a href="https://www.forth.com/">forth's website!</a>

Tenth is a very simple and straightforward programming language, really!

I'll show you...

# Examples:

## Pushing

To push a number onto the stack, you need to type:
    
    10

That's it, you pushed number 10!

## Adding

If you want to add some numbers, you can do it too! Here's how:

    10 15 +

If you want to print the result and pop the top of the stack, you can do it too, just type:

    10 15 + .

## Dump

What is "."? It's a opcode that pops the top of the stack and prints it on the screen. Dump.

## Show

There's more things in this language, for example, if you want to print the whole stack, you need to type this:

    10 25 42 88 90 show

What is "show". It's a opcode that prints the elements of the stack.

If want to do more math you can! Let me show you!

## Multiplying

For example, this expression: 2 + 2 * 2 can be written like this:

    2 2 * 2 + .

or some other expression like 2 - 2 * 2  - 2 can be written like this:

    -2 2 * 2 -2 - .

## Dividing

To divide an number in tenth, you need to type this:

    1 2 / .

## Comparing

To compare two numbers in tenth, you can!

5 is less than 10

    5 10 < .

This is going to be true, so the value thats going to be pushed onto stack is -1 representing true.

10 is greater than 50

    10 50 > .

This is going to be false, so the value that's going to be pushed onto stack is 0 representing false.

And finally

50 is equal to 50

    50 50 = .

This is going to be true, and you already know what value is going to be onto the stack...

## Duplicating

To duplicate top value onto stack, you need to have some other value onto stack to be able to duplicate it, so let's get to work:

    15 dup show

the result will be 
    
    15 15

## Droping

Droping is almost same as dumping, but you are not printing the value that you've poped from the top of the stack. To drop a value you need to have one already:

    10 show drop show

First we are going to push 10 and show the stack. Second we are going to call opcode drop, and then we are going to show stack again.

Result is going to be:

    10
    (empty)

## Swapping

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

## Rotate

Rot opcode is going to rotate first three elements onto stack. The third element from the top of the stack gets moved to the top of the stack, pushing the other two elements down.

    1 2 3 show
    rot show

Result:

    2 3 1

## Emit

Emit opcode is going to print ascii character.
Like this:

    65 emit

is going to print 'a' in the console.

## Exit

Exit is opcode that is going to terminate program with exit code.
Like this:

    420 exit

## Sizeof

Sizeof is opcode that is going to tell how many bytes does element have.
For example:

    10 sizeof

Result is 4

## Increment & Decrement

To increment top of the stack, you need to do this:

    15 inc .

If you want do decrement, you need to do this:
    
    15 dec .

## Output the string

Finally, i added string literals, so now you can push string onto stack. Like this:

    "Hello, World!" .

This is going to print Hello, World! in the console.