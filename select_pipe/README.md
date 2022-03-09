# Select Pipe

i/o multiplexing sample. named pipe edition.

## How

```bash
# main tty
$ make
$ ./main
```

```bash
# another tty
$ echo hello >> fifo1
$ echo hello >> fifo2
$ echo hello >> fifo3
```

then input via fifos above will display in main tty

```bash
# main tty
read 6 bytes from fd: 3
hello
read 6 bytes from fd: 4
hello
read 6 bytes from fd: 5
hello
```

