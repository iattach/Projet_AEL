app:main.o lex.o analy.o
	gcc main.o lex.o analy.o -o parser

main.o:main.c
	gcc -c main.c

lex.o:lex.c
	gcc -c lex.c

analy.o:analy.c
	gcc -c analy.c
