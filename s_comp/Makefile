source:all

all:clean main main1

main:
	@gcc main.c -o main

main1:
	@gcc with_morph.c -o main1


clean:
	@-rm main main1


test:clean_ut
	@gcc wm.ut.c -o wmut && ./wmut

clean_ut:
	@-rm wmut

