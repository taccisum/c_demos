# Zombie Process


# How

```bash
$ make
$ ./main
# child process 1 start
# parent process sleep 5s
# child process 2 start
# child process 2 sleep 10s
# parent process sleep 5s
# parent process exit

show zombie process in another tty

```bash
$ ps -o state,pid,ppid,uid,command | grep main
```

