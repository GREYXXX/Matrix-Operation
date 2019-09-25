#include "variables.h"

Matrix transpose(Matrix M, int threads)
{
	Matrix T;
	T.triples = malloc(sizeof(Triple) * (M.valueNum * 2));
	if(T.triples == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	
	T.colNum=M.rowNum;
	T.rowNum=M.colNum;
	T.valueNum=M.valueNum;

	omp_set_num_threads(threads);

	int k = 0;
	#pragma omp parallel 
	{
	#pragma omp for
	for(int i = 1; i <= M.colNum; i++){
		for(int j = 0; j < M.valueNum; j++){
			if(M.triples[j].col == i){
				T.triples[k].row = M.triples[j].col;
				T.triples[k].col = M.triples[j].row;
				T.triples[k].value = M.triples[j].value;
				printf("Assigned %f to position %d by THREAD: %d\n", M.triples[j].value, k, omp_get_thread_num());

				k++;
			}
		}

	}
	}
    	return T;
}
