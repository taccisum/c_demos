source:all

all:clean main main1 lexan

main:
	@gcc main.c -o main

main1:
	@gcc with_morph.c -o main1


lexan:
	@gcc lexan.c -o lexan
lexan_test:clean_ut
	@gcc lexan.test.c -o lexan_test && ./lexan_test


clean:
	@-rm main main1 lexan

test:clean_ut
	@gcc wm.ut.c -o wmut && ./wmut

clean_ut:
	@-rm wmut lexan_test

