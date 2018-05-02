#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])   // argv[1] will be address for 1st file and so on
{
	char *token = strtok(argv[1]," ");
	char *array[40];
	for(int i = 0;i<40;i++)
		array[i] = "NULL";
	int index = 0;
	while(token!=NULL)
	{
		array[index] = token;
		index++;
		token = strtok(NULL," ");
	}
	int start = 1;
	int add = 0;  // if add == 0 normal cat with some files  if add == 1 then -b option if add == 2 then -E option
	if (!strcmp(array[1],"NULL"))
	{
		char input[500];
		fgets(input,500,stdin);
		printf("%s\n",input);
	}
	else if (!strcmp(array[1],"-b"))
	{
		start = 2;
		add = 1;
	}
	else if (!strcmp(array[1],"-E"))
	{
		start = 2;
		add = 2;
	}
	else if (!strcmp(array[1],"-bE") || !strcmp(array[1],"-Eb"))
	{
		start = 2;
		add = 3;
	}
	int lineno = 1;
	for(int i = start;strcmp(array[i],"NULL");i++)
	{
		FILE *fp;
		char *line = NULL;
		size_t len = 0;
		int n;
		fp = fopen(array[i],"r");
		if (fp == NULL)
		{
			printf("can't find file %s\n",array[i]);
			continue;
		}
		while ((n = getline(&line, &len, fp)) != -1) 
		{
			line[n-1] = '\0';
			if (add == 0)
		 	   printf("%s\n", line);
		 	else if (add == 1)
		 	{
		 		if (!strcmp(line,"\n"))
		 			printf("%s\n",line);
		 		else
		 			printf("%d %s\n",lineno++,line);
		 	}
		 	else if (add == 2)
		 		printf("%s%s\n",line,"$");
		 	else if (add == 3)
		 	{
		 		if (!strcmp(line,"\n"))
		 			printf("%s$\n",line);
		 		else
		 			printf("%d %s$\n",lineno++,line);

		 	}

		}
		fclose(fp);
		    if (line)
		        free(line);
	}
	return 0;
}