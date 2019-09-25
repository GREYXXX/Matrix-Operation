#include "variables.h"

void printMatrix(Matrix P)
{
	int count = 0;
	int rowCount = 1;
	int colCount = 1;

	for(int i = 0; i < (P.rowNum * P.colNum); i++) {
		if(colCount > P.colNum) {
			colCount = 1;
			rowCount++;
		}
		if(P.triples[count].row == rowCount && P.triples[count].col == colCount) {
			printf("%f ", P.triples[count].value);
			count++;
		}
		else {
			printf("0 ");
		}
		colCount++;
	}
	printf("\n");

}
	
int writeMatrix(Matrix P, char *outputFile)
{
	FILE *fptr = fopen(outputFile, "w");
	if(fptr == NULL) {
		printf("Error!");
		exit(1);
	}

	int count = 0;
	int rowCount = 1;
	int colCount = 1;

	for(int i = 0; i < (P.rowNum * P.colNum); i++) {
		if(colCount > P.colNum) {
			colCount = 1;
			rowCount++;
		}
		if(P.triples[count].row == rowCount && P.triples[count].col == colCount) {
			fprintf(fptr, "%f ", P.triples[count].value);
			count++;
		}
		else {
			fprintf(fptr, "0 ");
		}
		colCount++;
	}

	if(outputFile[22] == 's') {
		return 1;
	}
	
	fclose(fptr);
	return 1;
}

//Generates and produces the output file based on current data and time
void produceOutputFile(char *outputFile)
{
	char buffer[32];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buffer, "%d", (tm.tm_mday));
	strcat(outputFile, buffer);

	int monthNum = tm.tm_mon+1;
	
	if(monthNum < 10) {
		strcat(outputFile, "0");
	}
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%d", monthNum);
	strcat(outputFile, buffer);
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%d", (tm.tm_year+1900)%2000);
	strcat(outputFile, buffer);
	strcat(outputFile, "_");

	memset(buffer, 0, sizeof(buffer));
	int hour = tm.tm_hour;
	if(hour < 10) {
		strcat(outputFile, "0");
	}
	sprintf(buffer, "%d", (tm.tm_hour));
	strcat(outputFile, buffer);

	int min =  tm.tm_min;
	if(min < 10) {
		strcat(outputFile, "0");
	}
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%d", (tm.tm_min));
	strcat(outputFile, buffer);
	strcat(outputFile, "_");
}

int main(int argc, char *argv[])
{
   	int c;		//Stores a value from getopt_long which determines whether success or failure
	int threads = 1;
	char command[3];//Stores the calculation to be executed for the matrix
	char inputFile1[32]; //Stores the file name
	char inputFile2[32]; //Stores another file name(if needed)
	char op[8];
	char *sm = "sm";
        char *tr = "tr";
        char *ad = "ad";
        char *ts = "ts";
        char *mm = "mm";

	char outputFile[32] ="21972786_";
	produceOutputFile(outputFile);
	printf("%s\n", outputFile);

	//Time Recording Definitions
	clock_t read_start, read_end, calc_start, calc_end;
	double cpu_time_used;

  	while (1) {	//Looks at arguments
		int this_option_optind = optind ? optind : 1;
        	int option_index = 0;
		static struct option long_options[] = {
			{"sm",  required_argument, 0,  'a' },	// '--sc' goes to case 'a', 'required_argument' expects an argument after '--sc'
			{"tr",  no_argument,       0,  'b' },	// 'no_argument' does not expect an argument after the initial argument
			{"ad",  no_argument,       0,  'c' },
			{"ts",  no_argument,       0,  'd' },
			{"mm",  no_argument,       0,  'e' },
			{0,         0,             0,   0  }
		};
		c = getopt_long(argc, argv, "a:bcdelf:t:",
			long_options, &option_index);

		if (c == -1)	//Argument fail
		    break;

		switch (c) {
		case 0:	//Default case
			break;
		case 'a':
		    	printf("Scalar Multiplication %s\n", optarg);
			strcpy(command, "sm");
			strcpy(op,optarg);	
		    	break;

	       	case 'b':
		    	printf("Trace\n");
			strcpy(command, "tr");		
		    	break;

	       	case 'c':
		    	printf("Addition\n");
			strcpy(command, "ad");
		    	break;

	       	case 'd':
		    	printf("Transpose\n");
			strcpy(command, "ts");
		    	break;
		case 'e':
			printf("Matrix Multiplication\n");
			strcpy(command, "mm");
			break;
	       	case 'f':
			strcpy(inputFile1, optarg);
			if(argv[optind]) {
				strcpy(inputFile2, argv[optind]);
				printf("File is %s and %s\n", inputFile1, inputFile2);
			}
			else {
				printf("File is %s\n", inputFile1);
			}
		    	break;
		case 't':
			printf("Number of Threads requested: %s\n",optarg);
			threads = atoi(optarg);
			break;
		case 'l':
			printf("Log\n");
			break;

	       	case '?':	//If the flag is not found, goes here
		    	break;

	       	default:
		printf("?? getopt returned character code 0%o ??\n", c);
		}
	}
	
	read_start = clock();
	Matrix M = readfile(inputFile1);
	Matrix N;
	if(argv[optind]) {
		N = readfile(inputFile2);
	}
	read_end = clock();
		
	calc_start = clock(); 
	if(strcmp(command,sm)==0){
		M = scalar(op,M, threads);
		strcat(outputFile, "sm.out");
		//printMatrix(M);
		writeMatrix(M, outputFile);
	}
	else if(strcmp(command,tr)==0){
		trace(M, threads);
		strcat(outputFile, "tr.out");
	}
	else if(strcmp(command,ts)==0){
		Matrix T = transpose(M, threads );
		strcat(outputFile, "ts.out");
		writeMatrix(T, outputFile);
/*
		for(int g = 0; g < T.valueNum; g++) {
			printf("G: %d ROW: %d COL: %d VALUE: %f\n", g, T.triples[g].row, T.triples[g].col, T.triples[g].value);
		}	
*/
		printMatrix(T);
	}
	else if(strcmp(command,ad)==0){
		//printf("Addition is underway\n");
		Matrix R = addition(M, N, threads);
		strcat(outputFile, "ad.out");
		writeMatrix(R, outputFile);
		//printMatrix(R);
	}
	else if(strcmp(command,mm)==0){
		Matrix P = multiplication(M, N);
		strcat(outputFile, "mm.out");
		writeMatrix(P, outputFile);
		//printMatrix(P);
	}
	calc_end = clock();
		
	cpu_time_used = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
	printf("%f\n", cpu_time_used);
	cpu_time_used = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;	
	printf("%f\n", cpu_time_used);	
	
	

	exit(EXIT_SUCCESS);
}
