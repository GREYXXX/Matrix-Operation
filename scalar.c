#include "variables.h"

Matrix scalar_mul(char *optarg, Matrix a)
{
	float v = atof(optarg);
	for(int i = 0; i < a.value_num; i++) {	
		a.data[i].value = (a.data[i].value) * v;
	}

	return a;
}
	
