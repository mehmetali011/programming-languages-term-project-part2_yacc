CC = gcc
CFLAGS = -g -Wall

all: plainscript

plainscript: plainscript.tab.c lex.yy.c runtime.c
	$(CC) $(CFLAGS) -o $@ $^

plainscript.tab.c: plainscript.y
	bison -d plainscript.y

lex.yy.c: plainscript.l
	flex plainscript.l

clean:
	rm -f plainscript plainscript.tab.* lex.yy.c program_log.txt