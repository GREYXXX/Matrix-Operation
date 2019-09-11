main: checkarg.o
	gcc -o main checkarg.o -lm
checkarg.o: checkarg.c variables.h
	gcc -c checkarg.c
