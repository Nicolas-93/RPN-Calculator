# NPN Calculator

This is a simple calculator that uses the NPN (Reverse Polish Notation) method to calculate the result of an expression.

## Buiding the project

To build the project, you need to run the following command:

```bash
$ make
```

## Running the project

To run the project, you need to run the following command:

```bash
$ ./build/rpn
```

## How to use

### Operators

To use the calculator, you need to type the expression in the following format:

```
<value1> <value2> <operator>
```

Where:

- `<value1>` is the first value of the expression
- `<value2>` is the second value of the expression
- `<operator>` is the operator that will be used to calculate the result of the expression (it can be `+`, `-`, `*`, `^`, `%` or `/`)

Unary operators are also supported. In this case, the expression should be in the following format:

```
<value> <operator>
```

Where:

- `<value>` is the value of the expression
- `<operator>` is the operator that will be used to calculate the result of the expression (it can be `!`)

Other operators can be easily added by a plugin system. To do that, you need to create a new file in the `src/operators` directory and implement the `Operator` interface (located in the `src/operators/operator_api.h` file). They will be automatically loaded by the calculator from the `build/plugins/operators` directory.

### Commands

The calculator also supports some commands that can be used to interact with it. The available commands are:

- `a`, `all` : Prints all the values in the stack
- `p`, `print` : Prints the stack's head
- `c`, `clear` : Clears the stack
- `r`, `reverse` : Reverses the stack's head
- `q`, `quit` : Quits the calculator

### Example

Here is an example of how to use the calculator:

```
>>> 5 5 + 2 *
>>> all
20 
>>> 0 /
Divide by 0
>>> all
20 0 
>>> clear
>>> 0 10 - !
Negative factorial
>>> clear
>>> 4294967295
Number too big
>>> -10 4294967 1000
>>> all
-10 4294967 1000 
>>> *
Integer overflow
>>> clear
>>> 2 8 ^
>>> all
256 
```
