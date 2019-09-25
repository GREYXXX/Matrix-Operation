/*	CITS3402 PROJECT
	Name:	Syukri Zainal Abidin
	Student Number: 21972786
*/
#include "variables.h"	

//This file reads the input and produces an internal representation for the matrix
Matrix readfile(char *optarg) {
	Matrix M;
	M.triples = malloc(sizeof(Triple));

        char *chr[4]; //The buffer to store each line of the input file

        FILE *fp = fopen(optarg, "r");
        if(fp == NULL) {
                perror("Unable to open file!");
                exit(1);
     	}
        int g = 0; //Character counter
	int h = 0; //Line counter
	char c; //The character
        char chunk[16384];	//Chunk represents a line in the input file
	char *dynamicChunk = malloc(256); //Allocate memory for the matrix line of the file, starts off with 256

	//fgetc allows for dynamic allocation
	while((c = fgetc(fp)) != EOF) {
		if(h == 3) { //if h==3, this is the line with the whole matrix
			dynamicChunk[g] = c;
			g++;
			if((g % 256) == 0) { //Every 256 characters, another 256 bytes are allocated
				dynamicChunk = realloc(dynamicChunk, g+256);	
			}
		}
		else if(c == '\n') {
			chunk[g] = '\0';
			chr[h] = strdup(chunk);
			g = 0;
			h++;
		}
		else {
			chunk[g] = c;
			g++;
		}
	}
	dynamicChunk[g] = '\0';
	chr[h] = strdup(dynamicChunk);
	g += 256;
	free(dynamicChunk);

	int row = atoi(chr[1]); //Max number of rows
	int col = atoi(chr[2]); //Max number of columns

	char *matrixLine = chr[3];

	int count = 0; //Keeps track of number of non-zero values 

	//Current row and column count
	int rowCount = 1;
	int colCount = 1;

	char *token = strtok(matrixLine, " ");
	if(atof(token) != 0) {
		M.triples[count].row = 1;
		M.triples[count].col = 1;
		M.triples[count].value = atof(token);
		count++;
		colCount++;
	}
	else {
		colCount++;
	}
	while(token != NULL) {
		if(rowCount == row && colCount > col) {
			break;
		}
		if(colCount > col) { 
			colCount = 1;
			rowCount++;
		}
		token = strtok(NULL, " ");
		if(atof(token) != 0) {
			M.triples = realloc(M.triples, sizeof(Triple) * (count+1));
			M.triples[count].row = rowCount;
			M.triples[count].col = colCount;
			M.triples[count].value = atof(token);
			count++;
			colCount++;

		}
		else {
			colCount++;
		}
	}

	M.valueNum = count; //Number of non-zero values
	M.rowNum = row; //Max number of rows
	M.colNum = col; //Max number of columns

        fclose(fp);
        for(int i = 0; i <4;i++) {
        	free(chr[i]);
	}
	return M;
}

