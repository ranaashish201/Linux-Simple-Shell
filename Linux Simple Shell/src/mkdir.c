#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int vbit = 0,pbit = 0;
	char *token = strtok(argv[1]," ");
	char *array[40];
	for(int i = 0;i<40;i++)	
		array[i] = "NULL";
	int index = 0;
	while(token!=NULL)
	{
		if (!strcmp(token,"-v"))
			vbit = 1;
		if (!strcmp(token,"-p"))
			pbit = 1;
		if (!strcmp(token,"-vp") || !strcmp(token,"-pv"))
			{
				vbit = 1;
				pbit = 1;
			}
		array[index] = token;
		index++;
		token = strtok(NULL," ");
	}
	if (!strcmp(array[1],"NULL"))
	{
		printf("%s\n","Missing operand");
		return 0;
	}
	if (array[1][0] == '-' && vbit == 0 && pbit == 0)
	{
		printf("%s\n","invalid argument");
		return 0;
	}
	int i = 1;
	while(strcmp(array[i],"NULL"))
	{
		if ((!strcmp(array[i],"-v"))  || !(strcmp(array[i],"-p")) || !(strcmp(array[i],"-vp"))  ||  !(strcmp(array[i],"-pv")))
			{
				i++;
				continue;
			}
		int status = mkdir(array[i],0777);
		if (vbit == 1)
		{
			printf("%s directory created\n",array[i]);
		}
		if (status == -1)
		{
			printf("%s\n","Error directory can't be created");
		}
		i++;
	}

	return 0;
}