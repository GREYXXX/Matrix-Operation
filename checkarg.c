
#include "variables.h"

int main(int argc, char *argv[])
{
   	int c;		//Stores a value from getopt_long which determines whether success or failure

	char *seg1 = malloc(sizeof(char)*4); //Stores file name
	char *seg2 = malloc(sizeof(char)*4); //Stores another file name(if needed)

    char **g = argv;
	g += 1;	
	printf("First argument is now: %s\n", g[0]);
	argc -= 1;
	c = getopt(argc, g, "f:t:l");
	printf("The case for 2nd argument: %i\n",c);
	/*if(c == -1){
		printf("Program failed\n");
		exit(EXIT_FAILURE);
	}*/
	
	switch(c) {
		case 'f':
			printf("File input\n");
			break;
		case 't':
			printf("Threads\n");
			break;
		case 'l':
			printf("Log\n");
			break;
	}
	//argv -= 1;
	//argc += 1;
	
	printf("Original first argument is: %s\n", argv[0]);
	
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

		c = getopt_long(argc, argv, "a:bcdef:",
			long_options, &option_index);
		printf("Case for 2nd argument is now: %i\n", c);
		if (c == -1)	//Argument fail
		    break;

		switch (c) {
		case 0:	//Default case
			break;
	    case 'a':
		    	printf("scalar multiplication %s\n", optarg);
			printf("Option index is: %i\n", option_index);
		    	break;

	       	case 'b':
		    	printf("trace\n");
			printf("Option index is: %i\n", option_index);
		    	break;

	       	case 'c':
		    	printf("addition\n");
			printf("Option index is: %i\n", option_index);

		    	break;

	       	case 'd':
		    	printf("transpose\n");
		    	break;
		case 'e':
			printf("Matrix multiplication\n");
			break;
	       	case 'f':
		    	//seg1 = optarg;
			strcpy(seg1, optarg);
		    	//seg2 = argv[optind];
			strcpy(seg2, argv[optind]);
		    	printf("File is %s and %s\n", seg1, seg2);
		    	break;

	       	case '?':
		    	break;

	       	default:
		printf("?? getopt returned character code 0%o ??\n", c);
		}
	}
		
	free(seg1);
	free(seg2);

	exit(EXIT_SUCCESS);
}
