#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "sysHeader.h"
#include "initUtil.h"

SysParam sys;

int init(int argc, char *argv[]){
    char c;
	char sptArg[256];
	memset(sptArg,0,256);
	int optIndex = 0;
	int rootPathLen = 0;	
#ifdef W32
    WSADATA wsaData;
#endif
    if (argc<2) return -1;
    
    while ((c = getopt(argc, argv, (char *)"a:b:c:e:f:i:k:l:m:n:o:p:q:r:s:t:u:w:y:z:d:vx?")) != EOF) {
        if (c == '?')
            return -1;
		snprintf(sptArg,256,"%s",optarg);
        switch (c) { 
        case 'a':
        	break;
		case 'i':
			optIndex = lastindexof(sptArg,"/");
			if(sptArg[0] == '.'){
				getcwd(sys.rootPath, 256);		
			}else{
				strncpy(sys.rootPath,sptArg,optIndex);
			}
			rootPathLen = strlen(sys.rootPath);
			if(sys.rootPath[rootPathLen - 1] != '/'){
				strcat(sys.rootPath,"/");
			}
			strcpy(sys.fileName,sptArg + optIndex + 1);
			strcpy(sys.filePath,sptArg);
			sprintf(sys.fileIndexPath,"%s.idx",sys.filePath);
			sprintf(sys.fileDataPath,"%s.dat",sys.filePath);
			break;
        case 'c':
			break;
        case 'd':
            break;
		case 'l':
            break;
		case 't':
			break;
		case 'm':
			break;
        default:
            return -1;
        }
    }  
	#ifdef W32
	WSAStartup(MAKEWRD(2,2), &wsaData);
#endif
    return 1;
}

void printUsage(char *sProg){
	    printf("%s -i filePath\n",sProg);
}


int main(int argc, char **argv){
	initSysParam(&sys);	
	if(init(argc,argv) != 1){ 
		printUsage(argv[0]);
		return -1; 
	}
	FILE * origFile = fopen(sys.filePath,"r");
	if(origFile){
		fclose(origFile);
		printf("open file [%s] err \n",sys.filePath);
	}
	FILE * indexFile = fopen(sys.fileIndexPath,"w+");
	if(indexFile){
		fclose(indexFile);
		printf("open file [%s] err \n",sys.fileIndexPath);
	}
	FILE * dataFile = fopen(sys.fileDataPath,"w+");
	if(dataFile){
		fclose(dataFile);
		printf("open file [%s] err \n",sys.fileDataPath);
	}
	char sLine[40960];
	while(fgets(sLine,SIZEOF_1(sLine),origFile) != 0){
		
	}
	fclose(origFile);
	fclose(indexFile);
	fclose(dataFile);
}
