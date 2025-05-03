plainscript: lex.yy.c y.tab.c
	gcc -g lex.yy.c y.tab.c runtime.c -o plainscript


lex.yy.c: y.tab.c plainscript.l
	lex plainscript.l

y.tab.c: plainscript.y
	yacc -d plainscript.y

clean: 
	rm -rf lex.yy.c y.tab.c y.tab.h plainscript plainscript.dSYM
