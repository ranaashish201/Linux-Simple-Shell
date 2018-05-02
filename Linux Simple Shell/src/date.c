#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int main(int argc, char const *argv[])
{
	char *weekday[] = {"Sun","Mon","Tue","Wed","Thurs","Fri","Sat"};
	char *month[] = {"Jan","Feb","March","April","May","June","July","Aug","Sep","Oct","Nov","Dec"};
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct tm tm2 = *gmtime(&t);
	if (!strcmp(argv[1],"date")  && !strcmp(argv[2],"NULL"))
		printf("%s %s %d %.2d:%.2d:%.2d  IST  %d\n",weekday[tm.tm_wday],month[tm.tm_mon],tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec,tm.tm_year+1900);
	else if (!strcmp(argv[1],"date") && !strcmp(argv[2],"-r")  && strcmp(argv[3],"NULL"))
	{
		struct stat attr;
		int status = stat(argv[3], &attr);  // status will be -1 if failed
		if(status < 0)
		{
			printf("Error: No such file\n");
			return 0;
		}
		printf("Last modified time: %s", ctime(&attr.st_mtime));
	}
	else if (!strcmp(argv[1],"date") && !strcmp(argv[2],"-u") && !strcmp(argv[3],"NULL"))   // -u command
	{
		printf("%s %s %d %.2d:%.2d:%.2d  UTC  %d\n",weekday[tm2.tm_wday],month[tm2.tm_mon],tm2.tm_mday,tm2.tm_hour,tm2.tm_min,tm2.tm_sec,tm2.tm_year+1900);
	}
	else
	{
		printf("Invalid command for date\n");
	}

	return 0;
}