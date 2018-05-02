#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	int fbit = 0,ibit = 0;
	char *token = strtok(argv[1]," ");
	char *array[40];
	for(int i = 0;i<40;i++)
		array[i] = "NULL";
	int index = 0;
	while(token!=NULL)
	{
		if (!strcmp(token,"-f"))
			fbit = 1;
		if (!strcmp(token,"-i"))
			ibit = 1;
		if (!strcmp(token,"-fi") || !strcmp(token,"-if"))
			{
				fbit = 1;
				ibit = 1;
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
	int i = 0;
	while(strcmp(array[i],"NULL"))
	{
		i++;
		if (!strcmp(array[i],"NULL"))
			break;
		if ((!strcmp(array[i],"-f"))  || !(strcmp(array[i],"-i")) || !(strcmp(array[i],"-fi"))  ||  !(strcmp(array[i],"-if")))
			continue;
		 if(fbit == 1  && ibit == 1)
		{
			int status = unlink(array[i]);
			if (status < 0)
				continue;
			printf("%s %s\n","file deleted",array[i]);
			continue;
		}
		if (ibit == 1)
		{
			printf("%s\n","Sure to delete ?  enter 1 for yes");
			int ch;
			scanf("%d",&ch);
			if (ch == 1)
			{
				int status = unlink(array[i]);
				if (fbit == 1)
					continue;
				if (status < 0)
				{
					if (fbit == 1)
						continue;
					printf("%s\n","File doesn't exist .");
					continue;
				}
			}
		}

		int status = unlink(array[i]);
		if (status < 0)
		{
			if (fbit == 0)
				printf("%s\n","File doesn't exist");
			// show error message
			//continue;
		}
	}
	return 0;

}