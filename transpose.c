/*	CITS3402 PROJECT
	Name:	Syukri Zainal Abidin
	Student Number: 21972786
*/
#include "variables.h"

Matrix transpose(Matrix M, int threads)
{
	Matrix T;
	T.triples = malloc(sizeof(Triple));
	if(T.triples == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	
	T.colNum=M.rowNum;
	T.rowNum=M.colNum;
	T.valueNum=M.valueNum;

	int k = 0;
	for(int i = 1; i <= M.colNum; i++){
		for(int j = 0; j < M.valueNum; j++){
			if(M.triples[j].col == i){
				T.triples[k].row = M.triples[j].col;
				T.triples[k].col = M.triples[j].row;
				T.triples[k].value = M.triples[j].value;
				T.triples = realloc(T.triples, sizeof(Triple) * (k + 2));
				k++;
			}
		}

	}
    	return T;
}
