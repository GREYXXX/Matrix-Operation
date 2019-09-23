#include "variables.h"

Matrix multiplication(Matrix M, Matrix N)
{
	Matrix P;
	P.triples = malloc(sizeof(Triple));

	double rowSum = 0;
	double M_valueFound = 0;
	double N_valueFound = 0;
	int x = 0; //Counter for new matrix number of nnz

	for(int rowCount = 1; rowCount <= M.rowNum; rowCount++) {	

		for(int bigcol = 1; bigcol <= M.colNum; bigcol++) {
		//Every iteration of bigcol, we get a rowSum
		for(int colCount = 1; colCount <= M.colNum; colCount++) {
			for(int i = 0; i < M.valueNum; i++) {
				if(M.triples[i].row == rowCount && M.triples[i].col == colCount) {
					M_valueFound = M.triples[i].value;	
					break;
				}
			}
			for(int j = 0; j < N.valueNum; j++) {
				if(N.triples[j].row == colCount && N.triples[j].col == bigcol) {
					N_valueFound = N.triples[j].value;
					break;
				}
			}
			rowSum += (M_valueFound * N_valueFound);
			M_valueFound = 0;
			N_valueFound = 0;
		}

		if(rowSum == 0) {
			continue;
		}

		P.triples[x].row = rowCount;
		P.triples[x].col = bigcol;	
		P.triples[x].value = rowSum;
		rowSum = 0;
		x++;
		P.triples = realloc(P.triples, sizeof(Triple) * (x+1));
	}

	}
	P.rowNum = M.rowNum;
	P.colNum = M.colNum;
	P.valueNum = x;
	return P;


}
