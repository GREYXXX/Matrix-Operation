#include <variables.h>

int main(int argc, char *argv[])
{
    int c;
    int digit_optind = 0;
    char *seg1 = (char*)malloc(sizeof(char)*4);
    char *seg2 = (char*)malloc(sizeof(char)*4);
    char *chr1[N];
    char *chr2[N];
    for(int k = 0; k < N;k++)
{   
        chr1[k]=(char*)malloc(sizeof(char)*4);
	chr2[k]=(char*)malloc(sizeof(char)*4);
}


   while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"sc",  required_argument, 0,  'a' },
            {"tr",  no_argument,       0,  'b' },
            {"ad",  no_argument,       0,  'c' },
            {"ts",  no_argument,       0,  'd' },
            {"mm",  no_argument,       0,  'e' },
            {0,         0,             0,   0  }
        };

       c = getopt_long(argc, argv, "a:bcdef:012",
                 long_options, &option_index);
        if (c == -1)
            break;

       switch (c) {
        case 0:
            //printf("option %s", long_options[option_index].name);
o            //if (optarg)
               // printf(" with arg %s", optarg);
            //printf("\n");
            //break;

       case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
              printf("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf("option %c\n", c);
            break;

       case 'a':
            printf("scalar multiplication\n");
            break;

       case 'b':
            printf("trace\n");
            break;

       case 'c':
	    printf("addition\n");
            printf("option c with value '%s'\n", optarg);
            break;

       case 'd':
	    printf("transpose\n");
            printf("option d with value '%s'\n", optarg);
            break;
       case 'f':
	    seg1 = optarg;
	    seg2 = argv[optind];
	    chr1 = readfile(seg1);
	    if(seg2){
		chr2 = readfile(seg2);
}
	    printf("is f hhhh\n");
	    printf("content %s\n", chr1[0]);
	    break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

   if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
    free(seg1);
    free(seg2);
    for(int i = 0; i < N;i++)
{   
        free(chr1[i]);
	free(chr2[i]);
}

   exit(EXIT_SUCCESS);
}
