#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 int hidden(const struct dirent *dir)
// post: returns 1/true if name of dir ends in .
{
	const char *s = dir->d_name;
	if (s[0] == '.')
		{
			return 0;
		}
	return 1;
}
int main(int argc, char const *argv[])
{
	struct dirent **namelist;
	int n; 
	int flag = 0;
	//printf("  reached in ls  \n");
	if (!strcmp(argv[1],"ls") && !strcmp(argv[2],"-a"))
	{
		n = scandir(".", &namelist, NULL, alphasort);
	}
	else if(!strcmp(argv[1],"ls"))
	{
		if (!strcmp(argv[2],"NULL"))
				n = scandir(".", &namelist, hidden, alphasort);
		else
			n = scandir(argv[2], &namelist, hidden, alphasort);
	//	printf(" n is %d\n",n);
	}
	else if (!strcmp(argv[1],"ls") && !strcmp(argv[2],"-m"))
	{
		n = scandir(".", &namelist, hidden, alphasort);
		flag = 1;
	}
	else if (!strcmp(argv[1],"ls") && (!strcmp(argv[2],"-am") || !strcmp(argv[2],"-ma")))
	{
		n = scandir(".", &namelist, NULL, alphasort);
		flag = 1;
	}
	else
	{
		n = -1;
	}
	if (n == -1) 
	{
		printf("%s\n","error while executing the command");
	    return 0;
	}
	for(int i = 0;i<n;i++)
	{
		if (flag ==0)
			printf("%s  ", namelist[i]->d_name);	
		if (flag == 1)
			printf("%s, ", namelist[i]->d_name);	
		free(namelist[i]);
	}
	printf("\n");
	free(namelist);
	return 0;
}