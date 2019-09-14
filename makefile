main: checkarg.o readfile.o scalar.o trace.o transpose.o
	gcc -o main checkarg.o readfile.o scalar.o trace.o transpose.o -lm

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

clean:
	rm -f *.o main
