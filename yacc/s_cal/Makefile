source:clean yacc lex comp

comp:
	@gcc main.c -o calculator -ll

yacc:
	@bison -ydv cal.y

lex:
	@lex -v cal.l

clean:
	@rm -f lex.yy.c calculator
