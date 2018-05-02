#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
const char *home;
const char *path;

void cd_(char *arg1,char *arg2)
{
	if (!strcmp(arg1,"NULL")  || !strcmp(arg1,"~"))
	{
		chdir(home);
		return;
	}
	if (arg1[0] == '~')//
	{
		char go[100];
		int i;
		for( i = 0;home[i]!='\0';i++)
			go[i] = home[i];
		for(int j = 1;arg1[j]!='\0';j++)
			go[i++] = arg1[j];
		go[i] = '\0';
		chdir(go);
		return;
	}
	int valid = chdir(arg1);
	if (valid < 0)
	{
		printf("%s\n","Error : can't find given path");
		return;
	}
}
void echo_(char *arr[])
{
	int i = 1;
	int flag = 0;
	if (!strcmp(arr[1],"-n"))
		{
			flag = 1;
			i = 2;
		}
	while(strcmp(arr[i],"NULL"))
		{
			printf("%s ",arr[i]);
			i++;
		}
		if (flag == 0)
			printf("\n");
}
int main(int argc, char const *argv[])
{
	FILE *fp;
	int index = 0;
	home = getenv("HOME");
	path = getenv("PWD");
	while(1)
	{
		char pathvariable[400];
		int x;
		for( x = 0;path[x]!='\0';x++)
			pathvariable[x] = path[x];
		pathvariable[x] = '\0';
		x = 0;
		char current_directory[1000];
		getcwd(current_directory,sizeof(current_directory));
		strcat(pathvariable,"/history.txt");
		//printf("%s\n",pathvariable);
		fp = fopen(pathvariable,"a");   // file pointer for reading history file
		chdir(current_directory);
		printf("%s %s$ ","@shell:~",current_directory);
		char command[200];
		char argument[200];
		fgets(command,200,stdin);
		if (fp)
		   {
			   fputs(command,fp);
		   }
		   fclose(fp);
		command[strcspn(command, "\n")] = '\0';
		int l = 0;
		for(;command[l]!='\0';l++)
			argument[l] = command[l];
		argument[l] = '\0';
		char *token = strtok(command," ");
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
		if (!strcmp(array[0],"cd"))  // cd command
		{
			cd_(array[1],array[2]);	
			continue;
		}
		else if (!strcmp(array[0],"pwd"))  // pwd command
		{
			if(array[1][0] == '-')
				printf("%s\n","can't find the command");
			else
				printf("%s\n",current_directory);
			continue;
		}
		else if (!strcmp(array[0],"echo"))
		{
			echo_(array);
			continue;
		}
		else if (!strcmp(array[0],"history"))
		{
			if (!strcmp(array[1],"NULL"))  // without arguments
			{
				FILE *f = fopen(pathvariable,"r");
				if (f!=NULL)
				{
				   char line [128]; 
				   while(fgets(line,sizeof(line),f)!=NULL) 
				   {
				      fputs(line,stdout);
				   }
				   fclose(f);
				}
				continue;
			}
			else if(!strcmp(array[1],"-c"))
			{
				fclose(fopen(pathvariable, "w"));
				continue;
			}
			else if (!strcmp(array[1],"-w"))
			{
				FILE *target = fopen(array[2],"w");
				FILE *source = fopen(pathvariable,"r");
				char arr[100];
				while(feof(source)==0){
					fprintf(target, "%s",arr );
					fgets(arr,256,source);
				}
				fclose(target);
				fclose(source);
			}
			else
			{
				printf("%s\n","Error: can't find the command");
			}
			continue;
		}
		else if (!strcmp(array[0],"exit"))
		{
			exit(0);
		}
		else if (strcmp(array[0],"ls") && strcmp(array[0],"cat") && strcmp(array[0],"date") && strcmp(array[0],"rm") && strcmp(array[0],"mkdir") )
		{
			printf("%s\n","Invalid command");
			continue;
		}
		char pathvariable2[400];
		for( x = 0;path[x]!='\0';x++)
			pathvariable2[x] = path[x];
		pathvariable2[x] = '\0';
		pid_t pid = fork();
		if (pid < 0)
			{
				printf("%s\n","Error occured while executing command");
				continue;
			}
		else	if (pid == 0) //child process
			{
				strcat(pathvariable2,"/");
				strcat(pathvariable2,array[0]);
				strcat(pathvariable2,".o");
				if (!strcmp(array[0],"ls"))
					execl(pathvariable2,"ls",array[0],array[1],NULL);
				if (!strcmp(array[0],"date"))
					execl(pathvariable2,"time",array[0],array[1],array[2],array[3],NULL);
				if (!strcmp(array[0],"rm"))
					{
						execl(pathvariable2,"rm",argument,NULL);
					}
				if(!strcmp(array[0],"cat"))
					execl(pathvariable2,"cat",argument,NULL);
				if(!strcmp(array[0],"mkdir"))
					{
						execl(pathvariable2,"mkdir",argument,NULL);
					}
			}
			else
				wait(NULL);

	}
	return 0;
}
