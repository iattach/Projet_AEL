app:main.o lex.o analysis.o 
	gcc main.o lex.o analysis.o -o parser

main.o:main.c
	gcc -c main.c

lex.o:lex.h lex.c
	gcc -c lex.c

analy.o:analysis.h analysis.c
	gcc -c analysis.c

clean:
	rm -rf *.o

