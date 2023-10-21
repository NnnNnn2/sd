#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printDirList ( DIR *pDIR, char *filePATH, bool l, bool a, bool A, bool n);
char *toBinary(int n, int len);
void printHelp();
//char *getFilePath(char *filePath, char *fileName);

int dirNum = 0;
char* directories[1000];

int main (int argc, char *argv[])
{
	DIR *pDIR;
	char *filePATH;
	bool dirFound = 0, l = 0, a = 0, A = 0, n = 0;
	
	for(int i=1;i<argc;i++)
	{
		char *arg = argv[i];
		//printf("%s\n",arg);
		
		if( strcmp( arg, "-l" ) == 0 )
		{
			l = true;
		}
		else if( strcmp( arg, "-a" ) == 0 )
		{
			a = true;
		}
		else if( strcmp( arg, "-A" ) == 0 )
		{
			A = true;
		}	
		else if( strcmp( arg, "-n" ) == 0 )
		{
			n = true;
		}
		else if( strcmp( arg, "--help" ) == 0 )
		{
			printHelp();
			exit(0);
		}
		else if( strcmp( arg, "--version" ) == 0 )
		{
			printf("version: 2.1.37\n");
			exit(0);
		}
		else
		{
			pDIR = opendir(arg);
			filePATH = arg;
			dirFound = 1;
			//printf("%s\n", filePATH);
		}
		
	}
	
	if(!dirFound)
	{
		pDIR = opendir(".");
		filePATH = ".";
		//printf("no directory given, using default directory\n");
	}
	
	if(pDIR == NULL)
	{
		fprintf(stderr, "%s %d: opendir() failed (%s)\n", __FILE__, __LINE__, strerror(errno));
		exit(-1);
	}
	printDirList ( pDIR, filePATH, l, a, A, n );
	
	return 0;
}

void printDirList ( DIR *pDIR, char *filePATH, bool l, bool a, bool A, bool n ) 
{
	int i = 0;
	struct dirent *pDirEnt;
	struct stat fileStat;
	struct passwd *pw;
	struct group  *gr;
	struct tm *modTime;
	char* fPATH;
	char fileName[100];
	DIR *nextdir;
	pDirEnt = readdir(pDIR);
	char next[100];
	printf("\n");
	while(pDirEnt != NULL)
	{
		strcpy(fileName,pDirEnt->d_name);
		if(filePATH==".")
		{
			fPATH=fileName;
		}
		else
		{
			char pathString[100];
			strcpy(pathString, filePATH);
			strcat(pathString, "/");
			strcat(pathString, fileName);
			fPATH=pathString;
		}
		stat(fPATH, &fileStat);
		pw = getpwuid(fileStat.st_uid);
		gr = getgrgid(fileStat.st_gid);
		char mtime[80];
    		time_t t = fileStat.st_mtime; 
    		modTime = localtime( &t );
    		strftime(mtime, sizeof mtime, "%a, %d %b %Y %T", modTime);
   		//printf("%s\n", mtime);
		if((a || pDirEnt->d_name[0] != '.') ||
			 ( A && strcmp(pDirEnt->d_name, ".") && strcmp(pDirEnt->d_name, "..")))
		{
			if( l || n )
			{
				//
				//printf("%s\t", toBinary(fileStat.st_mode,16));
				printf( (fileStat.st_mode & S_IFDIR) ? "d" : "-");
    				printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    				printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    				printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    				printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    				printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    				printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    				printf(". %d", pDirEnt->d_type);
    				if(l) printf("\t%s %s", pw->pw_name, gr->gr_name);
    				if(n) printf("\t%d %d", fileStat.st_uid, fileStat.st_gid);
 				printf("\t%d\t", fileStat.st_size);
 				printf("%s\t", mtime);
 				//
			}
			
			printf("%s\n", pDirEnt->d_name);
		}

		pDirEnt = readdir(pDIR);
	}
	closedir(pDIR);
}

void printHelp()
{
	printf(
"NAME\n       sd - list directory contents\nSYNOPSIS\n       sd [OPTION]... [FILE]...\nDESCRIPTION\n       List  information  about  the  FILEs  (the  current  directory  by\n       default). (It's ls but worse)\n	Arguments:\n       -a\n              do not ignore entries starting with .\n       -A\n              do not list implied . and ..\n       -l\n       	      use a long listing format\n       -n\n              like -l, but list numeric user and group IDs\n       --help \n       	      display this help and exit\n       --version\n              output version information and exit\nAUTHOR\n       Written by caffine addicted CS student.\nREPORTING BUGS\n       Meet me and tell me that my program sucks.\nCOPYRIGHT\n       Copyright  ©  2020 Free Software Foundation, Inc.  License GPLv3+:\n       GNU GPL version 3 or later <https//:gnu.org/licenses/gpl.html>.\n       This is free software: you are free to change and redistribute it.\n       There is NO WARRANTY, to the extent permitted by law.\nSEE ALSO\n       Funny YT video: https//:www.youtube.com/watch?v=dQw4w9WgXcQ\n	Another funny YT video: https://www.youtube.com/watch?v=SSUOTz3oWEQ\n	Another one: https://www.youube.com/watch?v=ETrhmFC_1TA\n");
}

/*
char *getFilePath(char *filePATH, char fileName[])
{
	if(filePATH==".")
	{
		return fileName;
	}
	else
	{
		char pathString[100];
		//printf("%d\n", strlen(filePATH));
		strcpy(pathString, filePATH);
		//printf("%s\n",pathString);
		strcat(pathString, "/");
		//printf("%s\n",pathString);
		strcat(pathString, fileName);
		printf("%s\n",pathString);
		return pathString;
	}
}
*/
char* toBinary(int n, int len)
{
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}
