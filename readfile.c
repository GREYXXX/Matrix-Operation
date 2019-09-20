#include "variables.h"	

char *removeSpaces(char *str)
{
	int count = 0;
	for( int i = 0; str[i]; i++) 
		if(str[i] != ' ')
			str[count++] = str[i];
	
	str[count] = '\0';
	return str;	
}

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

	char *matrixLine = chr[3];
	//matrixLine = removeSpaces(matrixLine);

	int numlen = 0; //Keeps track of length of number
	int count = 0; //Keeps track of number of non-zero values 
	bool numflag = false; //Checks whether there is a number detected

	//Current row and column count
	int rowCount = 1;
	int colCount = 1;
	char storeNum[5];	

	for(int i = 0; i < strlen(matrixLine) + 1; i++) {
		if(colCount > col) { 
			colCount = 1;
			rowCount++;
		}
		else if(matrixLine[i] == '0') {
			colCount++;	
			if(colCount > col) {
				colCount = 1;
				rowCount++;
			}
		}
		else if(matrixLine[i] == ' ' || matrixLine[i] == '\0') {
			if(numflag == true) {
				storeNum[numlen] = '\0';
				a.data[count].row = rowCount;
				a.data[count].col = colCount;
				a.data[count].value = atof(storeNum);
				//printf("ROW: %d COL: %d VALUE: %f\n", a.data[count].row, a.data[count].col, a.data[count].value);
				numflag = false;
				numlen = 0;
				count++;
				colCount++;
			}	
			else {
				continue;
			}
		}
		else {
			numflag = true;
			storeNum[numlen] = matrixLine[i];
			numlen++; 	
		}
	}

	//printf("ROW: %d COL: %d VALUE: %f\n", a.data[1].row, a.data[1].col, a.data[1].value);


	a.value_num = count; //Number of non-zero values
	a.row_num = row; //Max number of rows
	a.col_num = col; //Max number of columns

/* For Debugging purposes		
	for( int i = 0; i < a.value_num; i++) {
		printf("Value is: %f\n", a.data[i].value);
	}	
	printf("Number of non-zero values: %i\n", a.value_num);
*/		

        //fputs(chr,stdout);
        fclose(fp);
	return a;
        for(int a = 0; a <10;a++) {
        free(chr[a]);
	}
}

