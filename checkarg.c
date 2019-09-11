#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#define N 255

Matrix readfile(char *optarg) {
	Matrix a;
        char *chr[N];
        for(int k = 0; k < N;k++)
{       
        chr[k]=(char*)malloc(sizeof(char)*4);
}
        FILE *fp = fopen(optarg, "r");
        if(fp == NULL) {
                perror("Unable to open file!");
                exit(1);
     }
        int i=0;
        char chunk[128];
        while(fgets(chunk, sizeof(chunk), fp) != NULL){
                strcpy(chr[i],chunk);
                i++;
 }
	char *q = (char*)malloc(sizeof(char)*4);
	char *p = (char*)malloc(sizeof(char)*4);
	p = “int";
	q = "float";
	int row = atoi(chr[1]);
	int col = atoi(chr[2]);
	int k = 0;//counting the number of non-zero value
	//int t = 0; 
	for(int i = 0;i < row;i++)
{
		for(int j=0;i < col; i++)
			{
				a.data[k].row = i;
				a.data[k].col = j;
				if(chr[3][k]!='0'){
					if(strcmp(chr[0],p)==0){
						a.data[k].value = atoi(chr[3][k]);}
					if(strcmp(chr[0],q)==0){
						a.data[k].value = atof(chr[3][k]);}
					
					k++;
			}
				else	{countine;}
	}
}
	a.mu = row;
	a.nu = col;
	a.tu = k;
        //fputs(chr,stdout);
        fclose(fp);
	return a;
        for(int a = 0; a <10;a++)
{
        free(chr[a]);
}
	free(p);
	free(q);
}



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
