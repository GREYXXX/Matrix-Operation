#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct{
	int row;
	int col;
	double value;
}Triple;

typedef struct{
	Triple *triples;
	//Triple data[N];
	int rowNum, colNum, valueNum; //Max number of rows, columns and non-zero values
}Matrix;

//Global Functions
extern Matrix readfile(char *);
extern Matrix scalar(char *, Matrix, int);
extern void trace(Matrix, int);
extern Matrix addition(Matrix, Matrix, int);
extern Matrix transpose(Matrix);
extern Matrix multiplication(Matrix, Matrix);
