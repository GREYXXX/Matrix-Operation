#include "variables.h"

Matrix transpose(Matrix M)
{
	Matrix T;
	T.triples = malloc(sizeof(Triple));
	
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
				k++;
				T.triples = realloc(T.triples, sizeof(Triple) * (k+1));
			}
		}
	}
    	return T;
}
