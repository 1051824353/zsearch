#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "sysHeader.h"
#include "initUtil.h"
#include "linkUtil.h"

SysParam sys;

int init(int argc, char *argv[]){
    char c;
	char sptArg[256];
	memset(sptArg,0,256);
	int optIndex = 0;
	int rootPathLen = 0;
	int ret = 0;	
#ifdef W32
    WSADATA wsaData;
#endif
    if (argc<2) return -1;
    
    while ((c = getopt(argc, argv, (char *)"a:b:c:e:f:1ig:l:m:n:o:p:q:r:s:t:u:w:y:z:d:vx?")) != EOF) {
        if (c == '?')
            return -1;
		snprintf(sptArg,256,"%s",optarg);
        switch (c) { 
        case 'a':
        	break;
		case 'i':
			sys.opt = CREATE_INDEX;
			ret++;
			break;
        case 'f':
			optIndex = lastindexof(sptArg,"/");
			if(sptArg[0] == '.'){
				getcwd(sys.rootPath, 256);		
				strcpy(sys.fileName,sptArg + optIndex + 1);
			}else if(sptArg[0] != '/'){
				getcwd(sys.rootPath, 256);
				strcpy(sys.fileName,sptArg );
			}else{
				strncpy(sys.rootPath,sptArg,optIndex);
				strcpy(sys.fileName,sptArg + optIndex + 1);
			}
			rootPathLen = strlen(sys.rootPath);
			if(sys.rootPath[rootPathLen - 1] != '/'){
				strcat(sys.rootPath,"/");
			}
			strcpy(sys.filePath,sys.rootPath);
			strcat(sys.filePath,sys.fileName);
			sprintf(sys.fileIndexPath,"%s.idx",sys.filePath);
			sprintf(sys.fileDataPath,"%s.dat",sys.filePath);
			ret++;
			break;
        case 'g':
			sys.opt = FIND_DATA;
			strcpy(sys.grepChar,sptArg);
			ret++;
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
	if(ret == 2){
		return 1;
	}else{
	    return -1;
	}
}

void printUsage(char *sProg){
	    printf("%s\n-i -f filePath : create index\n-g -f filePath : find file\n",sProg);
}


int main(int argc, char **argv){
	initSysParam(&sys);	
	if(init(argc,argv) != 1){ 
		printUsage(argv[0]);
		return -1; 
	}
	chdir(sys.rootPath);
	
	if(sys.opt == CREATE_INDEX){
		FILE * origFile = fopen(sys.filePath,"r");
		if(!origFile){
			fclose(origFile);
			printf("open file [%s] err \n",sys.filePath);
		}
		FILE * indexFile = fopen(sys.fileIndexPath,"w+");
		if(!indexFile){
			fclose(indexFile);
			printf("open file [%s] err \n",sys.fileIndexPath);
		}
		FILE * dataFile = fopen(sys.fileDataPath,"w+");
		if(!dataFile){
			fclose(dataFile);
			printf("open file [%s] err \n",sys.fileDataPath);
		}
		LinkList *list = NULL;
		char sline[40960];
		while(fgets(sline,SIZEOF_1(sline),origFile) != 0){
			trimCrlf(sline);
			insertSortLinkList(&list,sline);		
		}
		int dataSeekIndex = 0;
		int listCount = getLinkListCount(list);
		
		if(fwrite(&listCount, sizeof(int), 1, indexFile)!=1){
			printf("write file [%s] err \n",sys.fileIndexPath);
		}
		for(int i = 0 ; i < listCount ; i ++){
			dataSeekIndex = ftell(dataFile) ;
			char * str = getLinkListVal(list,i);
			if(fwrite(str, strlen(str), 1, dataFile)!=1){
				printf("write file [%s] err \n",sys.fileDataPath);
				break;	
			}

			if(fwrite(&dataSeekIndex, sizeof(int), 1, indexFile)!=1){
				printf("write file [%s] err \n",sys.fileIndexPath);
				break;	
			}
		}
		fclose(origFile);
		fclose(indexFile);
		fclose(dataFile);
	}else if(sys.opt == FIND_DATA){
		FILE * indexFile = fopen(sys.fileIndexPath,"r");
		if(!indexFile){
			fclose(indexFile);
			printf("open file [%s] err \n",sys.fileIndexPath);
			return -1;
		}
		FILE * dataFile = fopen(sys.fileDataPath,"r");
		if(!dataFile){
			fclose(dataFile);
			printf("open file [%s] err \n",sys.fileDataPath);
			return -1;
		}
		char indexLine[40960];
		if(fgets(indexLine,40960,indexFile) == 0){
			printf("read file [%s] err \n",sys.fileIndexPath);
			return -1;
		}
		int count = (int)indexLine[0];	
		printf("read file count [%d] \n",count);
		
		int idxCount = count;
		int index = idxCount / 2 +1;
		while(idxCount-- > 0 && index <= count && index >=1){

			int dataIndex1 = indexLine[index * 4];
			int dataIndex2 = indexLine[index * 4 + 4];

			if (fseek(dataFile,dataIndex1,SEEK_SET) != 0){ 
				if (ferror(dataFile)){
					printf("seek file [%s] err \n",sys.fileDataPath);
					return -1;
				}   
			}
			char val[256];
			memset(val,0,256);
			int getStrLen = dataIndex2 - dataIndex1 + 1;
			if(getStrLen < 0 ){
				getStrLen = 256;
			}
			if(fgets(val,getStrLen,dataFile) == 0){
				printf("read file [%s] err \n",val);
			}
			int grepCharLen = strlen(sys.grepChar);
			int grepCmp = strncasecmp(val,sys.grepChar,grepCharLen);
			if(grepCmp == 0){
				printf("get string [%s] \n",val);
				return 1;
			}else if(grepCmp  > 0){
				index = (count - index) / 2;
			}else if(grepCmp < 0){
				index = (count - index) /2 + index + 1;
			}
		}
	}
}

