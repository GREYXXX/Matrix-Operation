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
	a.data = malloc(sizeof(Triple));

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
	char *dynamicChunk = malloc(256);
/*	
	while(fgets(chunk,sizeof(chunk), fp) != NULL) {
		chr[g] = strdup(chunk);
		g++;
	}
*/
	while((c = fgetc(fp)) != EOF) {
		if(h == 3) {
			dynamicChunk[g] = c;
			g++;
			if((g % 256) == 0) {
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
	//printf("%s\n", chr[3]);
	printf("Allocated a total of %d bytes!\n", g+256);
	free(dynamicChunk);
/*
	int c;
        while(fgets(chunk, sizeof(chunk), fp) != NULL){
		if(g == 3) {
			printf("This is last line: %d\n", g+1);
			while((c = fgetc(fp)) != EOF) {
				printf("%c\n", c);
			}
			break;
		}
		//printf("%s\n Length is %ld", chunk, strlen(chunk));
                strcpy(chr[g],chunk);	//Copies each line onto the buffer
		printf("This is line: %d\n Words are: %s", g+1, chr[g]);
                g++;
 	}
	exit(EXIT_FAILURE);
*/
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
	char storeNum[15]; //Stores the value in a character array

	for(int i = 0; i < strlen(matrixLine) + 1; i++) {
		//printf("%s\n", matrixLine);
		//printf("%ld\n", strlen(matrixLine));
		//exit(EXIT_FAILURE);
		if(colCount > col) { 
			colCount = 1;
			rowCount++;
		}
		if(matrixLine[i] == '.' && numflag == true) {
			storeNum[numlen] = matrixLine[i];
			numlen++;
			continue;
		}
		else if(matrixLine[i] == '.') { //If it is 0.0 , continue
			continue;
		}
		if(matrixLine[i] == '0' && numflag == false ) {
			continue;
/*
			colCount++;	
			if(colCount > col) {
				colCount = 1;
				rowCount++;
			}
*/
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
				a.data = realloc(a.data, sizeof(Triple) * (count+1));
				//printf("Memory allocated: %ld and value is: %f\n", sizeof(Triple) * (count+1), a.data[count-1].value);
				colCount++;
				continue;
			}
			colCount++;
			if(colCount > col) {
				colCount = 1;
				rowCount++;	
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

        fclose(fp);
        for(int i = 0; i <4;i++) {
        	free(chr[i]);
	}
	return a;
}

