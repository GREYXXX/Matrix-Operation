#include "variables.h"

Matrix addition(Matrix M, Matrix N, int threads)
{
	Matrix R; //The resultant matrix
	int maxNNZ = M.valueNum + N.valueNum; //The maximum possible number of non-zero values
	R.triples = malloc(sizeof(Triple)* maxNNZ);
	int count = 1; //Keeps track of number of values in R.triples

	if(M.rowNum != N.rowNum) {
		printf("Both matrices are of different sizes!\n");
		exit(EXIT_FAILURE);
	}	

	R.triples[0].value = 0;
	R.rowNum = M.rowNum;
	R.colNum = M.colNum;

	int i, j;
	omp_set_num_threads(threads);
	#pragma omp parallel for reduction (+:count)
	for(i = 0; i < M.valueNum; i++) {
		R.triples[i].row = M.triples[i].row;
		R.triples[i].col = M.triples[i].col;
		R.triples[i].value += M.triples[i].value;
		//R.triples = realloc(R.triples, sizeof(Triple) * (count+1));
		count++;
	}

	#pragma omp parallel for reduction (+:count)
	for(j = 0; j < N.valueNum; j++) {
		R.triples[j].row = N.triples[j].row;
		R.triples[j].col = N.triples[j].col;
		R.triples[j].value += N.triples[j].value;
		//R.triples = realloc(R.triples, sizeof(Triple) * (count+1));
		count++;
	}

	R.valueNum = count - 1;

	return R;

}
