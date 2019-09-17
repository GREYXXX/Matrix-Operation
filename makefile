main: checkarg.o readfile.o scalar.o trace.o transpose.o addition.o
	gcc -o main checkarg.o readfile.o scalar.o trace.o transpose.o addition.o -lm

readfile.o: readfile.c variables.h
	gcc -c readfile.c

scalar.o: scalar.c variables.h
	gcc -c scalar.c

trace.o: trace.c variables.h
	gcc -c trace.c

transpose.o: transpose.c variables.h
	gcc -c transpose.c

checkarg.o: checkarg.c variables.h
	gcc -c checkarg.c

addition.o: addition.c variables.h
	gcc -c addition.c

clean:
	rm -f *.o main
