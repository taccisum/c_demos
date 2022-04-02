# Simple Compiler


# How

```bash
$ make
```

## infrx expr -> postfix expr

only support operators '+', '-', and unit digit. can not exists any space in expr str.

```bash
$ ./main 9-5+2
95-2+
$ ./main 8-3+2-4
83-2+4-
```

## simple lexeme parser

A simple implementation of lexeme parser.

It can parse patterns below(auto skip empty space between lexemes):

- ID: letter(letter|digit)*
- Number: digit+
- Operator: [+-*/]

```bash
$ ./lexan "1+2-3*4/x0"
1(Number)
+(Operator)
2(Number)
-(Operator)
3(Number)
*(Operator)
4(Number)
/(Operator)
x0(ID)
```



