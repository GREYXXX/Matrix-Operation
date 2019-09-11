
#include "variables.h"

int main(int argc, char *argv[])
{
   	int c;		//Stores a value from getopt_long which determines whether success or failure
	char command[3];//Stores the calculation to be executed for the matrix
	char *seg1 = malloc(sizeof(char)*4); //Stores file name
	char *seg2 = malloc(sizeof(char)*4); //Stores another file name(if needed)

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
		    	printf("scalar multiplication %s\n", optarg);
			strcpy(command, "sm");	
		    	break;

	       	case 'b':
		    	printf("trace\n");
			strcpy(command, "tr");		
		    	break;

	       	case 'c':
		    	printf("addition\n");
			strcpy(command, "ad");
		    	break;

	       	case 'd':
		    	printf("transpose\n");
			strcpy(command, "ts");
		    	break;
		case 'e':
			printf("Matrix multiplication\n");
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
			printf("Threads\n");
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
		
	free(seg1);
	free(seg2);

	exit(EXIT_SUCCESS);
}
