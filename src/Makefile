CC = gcc

CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o tree.o printer.o
	$(CC) lex.yy.o parser.tab.o main.o -o ../minilang -lfl

parser.tab.c parser.tab.h: minilang.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h minilang.y

lex.yy.c: minilang.l parser.tab.h
	flex minilang.l
clean:
	rm parser.tab.* lex.yy.*; rm *.o