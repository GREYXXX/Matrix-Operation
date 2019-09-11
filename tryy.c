#include "stdio.h"
#include "stdlib.h"
#define N 50
int main(int argc,char *argv[])
{
	FILE *fp;
	char line[N];
	char buffer[N];
	//char *buffer = malloc(N * sizeof(int));
	//char *temp = malloc(N * sizeof(int));
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("can not load file!");
		return 1;
	}
	//fgets(line,50,fp);
	//printf("%s\n",line);
	if(fgets(line,50,fp)!=NULL)
	{
		fputs(line,stdout);
		//printf("%s\n",line);
	}
	//for(int i = 0;i < sizeof(line); i++)
//{
	//buffer[i] = line[i];
//}
	//printf("%s\n",buffer[1]);
	//printf("%s\n",line);
	fclose(fp);
	return 0;
}

