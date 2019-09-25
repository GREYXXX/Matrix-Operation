/*	CITS3402 PROJECT
	Name:	Syukri Zainal Abidin
	Student Number: 21972786
*/
#include "variables.h"

double trace(Matrix M, int threads)
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
	return sum;

}
