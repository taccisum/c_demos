source:all

all:main bq

main:clean
	@gcc main.c -o main -lm -pthread && ./main

bq:clean
	@gcc blocked_queue.c -o bq -pthread && ./bq

clean:
	@-rm main, blocked_queue

