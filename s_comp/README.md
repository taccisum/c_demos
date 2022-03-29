# Simple Compiler


# How

## infrx expr -> postfix expr

only support operators '+', '-', and unit digit. can not exists any space in expr str.

```bash
$ make
$ ./main 9-5+2
95-2+
$ ./main 8-3+2-4
83-2+4-
```

