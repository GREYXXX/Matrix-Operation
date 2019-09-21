#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <getopt.h>
#include <stdbool.h>
#define N 10000 

typedef struct{
	int row;
	int col;
	double value;
}Triple;

typedef struct{
	Triple *data;
	//Triple data[N];
	int row_num, col_num, value_num;
}Matrix;

//Global Functions
extern Matrix readfile(char *);
extern Matrix scalar_mul(char *, Matrix);
extern int trace(Matrix);
extern Matrix addition(Matrix, Matrix);
extern Matrix transposeMatrix(Matrix);
