#include "variables.h"

Matrix printMatrix(Matrix C)
{
	int count = 0;
	int rowCount = 1;
	int colCount = 1;

	for(int i = 0; i < (C.row_num * C.col_num); i++) {
		if(colCount > C.col_num) {
			colCount = 1;
			rowCount++;
		}
		if(C.data[count].row == rowCount && C.data[count].col == colCount) {
			printf("%f ", C.data[count].value);
			count++;
		}
		else {
			printf("0 ");
		}
		colCount++;
	}
	printf("\n");
	//printf("ROW %d and COL %d\n", C.data[1].row, C.data[1].col);

}

int main(int argc, char *argv[])
{
   	int c;		//Stores a value from getopt_long which determines whether success or failure
	char *command = malloc(sizeof(char));//Stores the calculation to be executed for the matrix
	//char *seg1 = malloc(sizeof(char)); //Stores file name
	char seg1[N];
	char *seg2 = malloc(sizeof(char)); //Stores another file name(if needed)
	char *op = malloc(sizeof(char));
	char *sm = "sm";
        char *tr = "tr";
        char *ad = "ad";
        char *ts = "ts";
        char *mm = "mm";

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
			strcpy(seg1, optarg);
			if(argv[optind]) {
				strcpy(seg2, argv[optind]);
				printf("File is %s and %s\n", seg1, seg2);
			}
			else {
				printf("File is %s\n", seg1);
			}
		    	break;
		case 't':
			printf("Number of Threads requested: %s\n",optarg);
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
	Matrix m = readfile(seg1);
	Matrix n;
	if(argv[optind]){
		n = readfile(seg2);
	}
		 
	if(strcmp(command,sm)==0){
		m = scalar_mul(op,m);
		printMatrix(m);
	}
	else if(strcmp(command,tr)==0){
		trace(m);
	}
	else if(strcmp(command,ts)==0){
		m = transposeMatrix(m);
		printMatrix(m);
	}
	else if(strcmp(command,ad)==0){
		//printf("Addition\n");
		m = addition(m, n);
		printMatrix(m);
	}
	else if(strcmp(command,mm)==0){
		printf("Feature not available yet\n");
		//multiply();
	}
			
		
	free(op);		
	//free(seg1);
	free(seg2);

	exit(EXIT_SUCCESS);
}
