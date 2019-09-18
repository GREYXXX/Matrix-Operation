#include "variables.h"	

//This file reads the input and produces an internal representation for the matrix
Matrix readfile(char *optarg) {
	Matrix a;
        char *chr[N]; //The buffer to store each line of the input file
        for(int k = 0; k < N;k++) {	//Allocating memory for each pointer in pointer array(chr)
        	chr[k]=(char*)malloc(sizeof(char)*4);
	}
        FILE *fp = fopen(optarg, "r");
        if(fp == NULL) {
                perror("Unable to open file!");
                exit(1);
     	}
        int i=0;
        char chunk[128];	//Chunk represents a line in the input file
        while(fgets(chunk, sizeof(chunk), fp) != NULL){
                strcpy(chr[i],chunk);	//Copies each line onto the buffer
                i++;
 	}

	//p and q are used to compare the elements in the array and determine whether they are integers or floats
	int row = atoi(chr[1]); //Max number of rows
	int col = atoi(chr[2]); //Max number of columns
	int k = 0;//counting the number of non-zero value
	//int t = 0; 
	
	for(int i = 0;i < row;i++) {
		for(int j=0;j < col; j++) {
				a.data[k].row = i;
				a.data[k].col = j;
				if(chr[3][k]!='0'){
					a.data[k].value = atof(&chr[3][k]);
					k++;
			}
				else	{continue;}
		}
	}
	a.row_num = row; //Max number of rows
	a.col_num = col; //Max number of columns
	a.value_num = k + 1; //Number of non-zero values
        //fputs(chr,stdout);
        fclose(fp);
	return a;
        for(int a = 0; a <10;a++) {
        free(chr[a]);
	}
}

