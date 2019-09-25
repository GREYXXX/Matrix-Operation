main: checkarg.o readfile.o scalar.o trace.o addition.o transpose.o multiplication.o
	gcc -fopenmp -o main checkarg.o readfile.o scalar.o trace.o addition.o transpose.o multiplication.o -lm

readfile.o: readfile.c variables.h
	gcc -c readfile.c

scalar.o: scalar.c variables.h
	gcc -fopenmp -c scalar.c

trace.o: trace.c variables.h
	gcc -fopenmp -c trace.c

transpose.o: transpose.c variables.h
	gcc -fopenmp -c transpose.c

checkarg.o: checkarg.c variables.h
	gcc -c checkarg.c

addition.o: addition.c variables.h
	gcc -fopenmp -c addition.c

multiplication.o: multiplication.c variables.h
	gcc -fopenmp -c multiplication.c variables.h

clean:
	rm -f *.o main
