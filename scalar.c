#include "variables.h"

Matrix scalar(char *optarg, Matrix M, int threads)
{
	double m = atof(optarg); //The number to be multiplied by
	omp_set_num_threads(threads);
	int i;
	#pragma omp parallel for
	for(i = 0; i < M.valueNum; i++) {	
		M.triples[i].value = (M.triples[i].value) * m;
		//printf("NNZ VALUE: %i Parallel region thread: %d\n", i, omp_get_thread_num());

	}

	return M;
}
	
