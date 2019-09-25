/*	CITS3402 PROJECT
	Name:	Syukri Zainal Abidin
	Student Number: 21972786
*/


#include "variables.h"

bool logflag = false;

//Prints the matrix to terminal
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
	
//Writes the matrix to file
int writeMatrix(Matrix P, char *outputFile, char *command, char *inputFile1, char *inputFile2, double read_time, double calc_time, int threads)
{
	if(logflag == false) {
		printf("%s\n", command);
		printf("%s\n", inputFile1);
		if(inputFile2) {
			printf("%s\n", inputFile2);
		}
		printf("%d\n", threads);	
		printMatrix(P);
		printf("%f\n", read_time);
		printf("%f\n", calc_time);
		return 1;
	}


	FILE *fptr = fopen(outputFile, "w");
	if(fptr == NULL) {
		printf("Error!");
		exit(1);
	}

	int count = 0;
	int rowCount = 1;
	int colCount = 1;

	fprintf(fptr, "%s\n", command);
	fprintf(fptr, "%s\n", inputFile1);
	if(inputFile2) {
		fprintf(fptr, "%s\n", inputFile2);
	}
	fprintf(fptr, "%d\n", threads);
	

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



	fprintf(fptr, "\n%f\n", read_time);
	fprintf(fptr, "%f\n", calc_time);

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

	char outputFile[32] ="21972786_"; //outputfile name
	produceOutputFile(outputFile);

	//Time Recording Definitions
	clock_t read_start, read_end, calc_start, calc_end;
	double read_time, calc_time;

  	while (1) {	//Looks at arguments
		int this_option_optind = optind ? optind : 2;
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
			strcpy(command, "sm");
			strcpy(op,optarg);	
		    	break;

	       	case 'b':
			strcpy(command, "tr");		
		    	break;

	       	case 'c':
			strcpy(command, "ad");
		    	break;

	       	case 'd':
			strcpy(command, "ts");
		    	break;
		case 'e':
			strcpy(command, "mm");
			break;
	       	case 'f':
			strcpy(inputFile1, optarg);
			if(argv[optind]) {
				strcpy(inputFile2, argv[optind]);
			}
		    	break;
		case 't':
			threads = atoi(optarg);
			break;
		case 'l':
			logflag = true;
			break;

	       	case '?':	
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
		calc_end = clock();
		read_time = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
		calc_time = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;	
		writeMatrix(M, outputFile, command, inputFile1, NULL, read_time, calc_time, threads);
	}
	else if(strcmp(command,tr)==0){
		double traceResult = trace(M, threads);
		strcat(outputFile, "tr.out");
		calc_end = clock();
		read_time = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
		calc_time = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;
		if(logflag == false) {
			printf("%s\n", command);
			printf("%s\n", inputFile1);
			printf("%d\n", threads);
			printf("%f\n", traceResult);
			printf("%f\n%f\n", read_time, calc_time);
		}	
		else {
			FILE *fptr = fopen(outputFile, "w");
			if(fptr == NULL) {
				printf("Error!");
				exit(1);
			}
			fprintf(fptr, "%s\n", command);
			fprintf(fptr, "%s\n", inputFile1);
			fprintf(fptr, "%d\n", threads);
			fprintf(fptr, "%f\n", traceResult);
			fprintf(fptr, "%f\n%f\n", read_time, calc_time);
			fclose(fptr);
		}
		
	}
	else if(strcmp(command,ts)==0){
		Matrix T = transpose(M, threads );
		strcat(outputFile, "ts.out");
		calc_end = clock();
		read_time = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
		calc_time = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;	
		writeMatrix(T, outputFile, command, inputFile1, NULL, read_time, calc_time, threads);
	}
	else if(strcmp(command,ad)==0){
		Matrix R = addition(M, N, threads);
		strcat(outputFile, "ad.out");
		calc_end = clock();
		read_time = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
		calc_time = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;	
		writeMatrix(R, outputFile, command, inputFile1, inputFile2, read_time, calc_time, threads);
	}
	else if(strcmp(command,mm)==0){
		Matrix P = multiplication(M, N, threads);
		strcat(outputFile, "mm.out");
		calc_end = clock();
		read_time = ((double) (read_end - read_start)) / CLOCKS_PER_SEC;	
		calc_time = ((double) (calc_end - calc_start)) / CLOCKS_PER_SEC;	
		writeMatrix(P, outputFile, command, inputFile1, inputFile2, read_time, calc_time, threads);
	}

	exit(EXIT_SUCCESS);
}
