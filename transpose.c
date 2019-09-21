#include "variables.h"

Matrix transposeMatrix(Matrix M){
	Matrix T;
	T.data = malloc(sizeof(Triple));
	
	T.col_num=M.row_num;
	T.row_num=M.col_num;
	T.value_num=M.value_num;

	int k = 0; 
	for(int i = 1; i <= M.col_num; i++){
		for(int j = 0; j < M.value_num; j++){
			if(M.data[j].col == i){
				T.data[k].row = M.data[j].col;
				T.data[k].col = M.data[j].row;
				T.data[k].value = M.data[j].value;
				k++;
				T.data = realloc(T.data, sizeof(Triple) * (k+1));
			}
		}
	}
    	return T;
}
