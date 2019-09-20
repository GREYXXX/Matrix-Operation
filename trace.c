#include "variables.h"

int trace(Matrix a)
{
	if(a.row_num != a.col_num) {
		printf("It's not a square matrix\n");
		exit(EXIT_FAILURE);	
	}

	float sum = 0;

	for(int i = 0;i < a.value_num; i++) {
		if(a.data[i].row == a.data[i].col){
			sum = sum + a.data[i].value;
		}
	
	}
	printf("%f\n", sum);

	return sum;
}
