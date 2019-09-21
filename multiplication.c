#include "variables.h"

Matrix multiplication(Matrix A, Matrix B)
{
	Matrix C;
	int a_row, b_row;
	int p, q, t, ccol, tp;
	int ctemp[N];

	if(A.col_num != B.row_num){
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}

	C.row_num = A.row_num;
	C.col_num = B.col_num;
	if(A.value_num*B.value_num != 0){ //IF NOT ZERO MATRIX
		for(a_row = 1;a_row <= A.row_num;a_row++){
			for(int k = 1; k <= A.col_num;k++){
				ctemp[k] = 0;//INITIALNIZING ALL OF ACCUMULATOR
			}

			C.F[a_row] = C.value_num + 1;
			if (a_row < A.row_num) 
				tp = A.F[a_row + 1];//MOVE TO FIRST NON-ZERO ELEMENTS OF NEXT ROW FOR MATRIX A;
			else 
				tp = A.value_num + 1;
			for (p = A.F[a_row]; p < tp; ++p) {    
				b_row = A.data[p].col;//FIND THE ROW OF MATRIX B
				if (b_row < B.row_num) 
					t = B.F[b_row + 1];//MOVE TO FIRST NON-ZERO ELEMENTS OF NEXT ROW FOR MATRIX B;
				else 
					t = B.value_num + 1;
				for (q = B.F[b_row]; q< t; ++q) 
				{
					ccol = B.data[q].col;
					ctemp[ccol] += A.data[p].value * B.data[q].value;
				}
			}
			for (ccol = 1; ccol <= C.col_num; ++ccol)
			if (ctemp[ccol]) 
			{
				if (++C.value_num > N - 1){ 
					printf("SIZE ERROR\n");
					exit(EXIT_FAILURE);
				}
				C.data[C.value_num].row = a_row;
				C.data[C.value_num].col = ccol;
				C.data[C.value_num].value = ctemp[ccol];
			}
		} 
	}
	return C;
} 
			
