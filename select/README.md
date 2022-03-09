# Select

i/o multiplexing sample. unix select() edition.

## How

```bash
$ make
```

create tty1 & tty2 via your terminal and get they relevant char device file. like case below

```bash
# in tty1
$ tty
/dev/ttys013
```

```bash
# in tty2
$ tty
/dev/ttys015
```

then pass tty file paths as arguments

```bash
# in another tty run main program
$ ./main /dev/ttys013 /dev/ttys015
open tty1: /dev/ttys013
open tty2: /dev/ttys015
fds:3(tty1), 4(tty2)
```

now you can put any character into tty1 or tty2 by using keyboard. then the chars will display in tty that running main

```text
read from fd: 4
j
read from fd: 4
k
read from fd: 3
a
read from fd: 3
b
```


