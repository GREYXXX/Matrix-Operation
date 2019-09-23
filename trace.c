#include "variables.h"

void trace(Matrix M, int threads)
{
	if(M.rowNum != M.colNum) {
		printf("Not a square matrix\n");
		exit(EXIT_FAILURE);	
	}

	double sum = 0;

	omp_set_num_threads(threads);
	#pragma omp parallel for reduction (+:sum)

	for(int i = 0;i < M.valueNum; i++) {
		if(M.triples[i].row == M.triples[i].col){
			sum += M.triples[i].value;
		}
	
	}
	printf("%f\n", sum);

}
