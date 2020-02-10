CC = gcc

CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o
	$(CC) lex.yy.o parser.tab.o main.o -o ../minlang -lfl

parser.tab.c parser.tab.h: minlang.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h minlang.y

lex.yy.c: minlang.l parser.tab.h
	flex minlang.l
clean:
	rm parser.tab.* lex.yy.*; rm *.o