# lock

sample of file lock.

## How

```bash
$ make
```

run slave

```bash
$ ./slave
# no hang
```

run slave after main

```bash
$ ./main
# lock until exit
```

```bash
# another tty
$ ./slave
# slave hang until main exit(because the lock is holding by main)
```

