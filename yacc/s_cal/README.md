# Simple Calculator

This is a simple calculator write with yacc(bison).

Supports:

- Operator: + - * / ( )
- Operand: natural number[0, +∞]

# How

```bash
$ make
$ ./calculator
> 1+2*3;
to postfix: 123*+
calculating result: 7
> (1+2)*3;
to postfix: 12+3*
calculating result: 9
```
