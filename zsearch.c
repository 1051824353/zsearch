#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "sysHeader.h"
#include "initUtil.h"
#include "linkUtil.h"
#include "treeUtil.h"
#include "hashUtil.h"

#include<iostream>
#include <set>
#include <string>
using namespace std;

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

struct strLess{
	bool operator()(string s1,string s2) const{
		return s1.compare(s2) < 0;
	}
};

int main(int argc, char **argv){
	initSysParam(&sys);	
	if(init(argc,argv) != 1){ 
		printUsage(argv[0]);
		return -1; 
	}
	chdir(sys.rootPath);
	int count = 0;	
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
		set<string,strLess> list;
		char sline[40960];
		count = 0;
		while(fgets(sline,SIZEOF_1(sline),origFile) != 0){
			trimCrlf(sline);
			string str = string(sline);
			list.insert(str);
			++count;
			if(count % 10000 == 0){
				printf("get str num[%d]\n",count);
			}
		}
		int count = list.size();
		if(fwrite(&count, sizeof(int), 1, indexFile)!=1){
			printf("write file [%s] err \n",sys.fileIndexPath);
		}
		printf("out count[%d]\n",count);
		
		count = 0;

		int dataSeekIndex = 0;
		set<string,strLess>::iterator it;
		for(it=list.begin();it!=list.end();it++){
			string tmpstr = *it;
			const char * tmpchar = tmpstr.c_str();
			if(fwrite(tmpchar, strlen(tmpchar), 1, dataFile)!=1){
				printf("write file [%s] err \n",sys.fileDataPath);
				break;	
			}
			dataSeekIndex = ftell(dataFile) ;
			if(fwrite(&dataSeekIndex, sizeof(int), 1, indexFile)!=1){
				printf("write file [%s] err \n",sys.fileIndexPath);
				break;	
			}
			++count;
			if(count % 10000 == 0){
				printf("out str num[%d]\n",count);
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
		count = 0;
		int * indexLine = NULL;
		readMemFile((char **)&indexLine,indexFile);
		fclose(indexFile);

		count = indexLine[0];
		printf("read file count [%d] \n",count);
	
		


		int idxCount = count;
		int index = idxCount / 2 +1;
		char val[256];
		int dataIndex1 = 0,dataIndex2 = 0;
		int grepCmp = 0;
		
		int oldIndex = 0;
		while(idxCount-- > 0 && index <= count && index >=1){
			dataIndex1 = indexLine[index];
			dataIndex2 = indexLine[index+1];
			

			if (fseek(dataFile,dataIndex1,SEEK_SET) != 0){ 
				if (ferror(dataFile)){
					printf("seek file [%s] err \n",sys.fileDataPath);
					return -1;
				}   
			}
			memset(val,0,256);
			int getStrLen = dataIndex2 - dataIndex1 + 1;
			if(getStrLen < 0 ){
				getStrLen = 256;
			}
			if(fgets(val,getStrLen,dataFile) == 0){
				printf("read file [%s] err \n",val);
			}
			int grepCharLen = strlen(sys.grepChar);
			grepCmp = strncasecmp(val,sys.grepChar,grepCharLen);
			if(grepCmp == 0){
				printf("get string [%s] \n",val);
				return 1;
			}
			int diffIndex = abs(oldIndex-index);
			if(diffIndex > 100){
				oldIndex = index;
				if(grepCmp  > 0){
					index -= diffIndex /2;
				}else if(grepCmp < 0){
					index += diffIndex /2;
				}
			}else{
				if(grepCmp  > 0){
					index--;
				}else if(grepCmp < 0){
					index++;
				}
			}

		}
		FREE_OBJ(indexLine);
		fclose(dataFile);
	}
}

