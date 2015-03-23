#include "fileUtil.h"

int getFilePath(int type,SysParam * sp,char * filePath,int filePathLen){
		memset(filePath,0,filePathLen);
		
		int rootLength = strlen(sp->rootPath);
		if(sp->rootPath[rootLength - 1] != '/'){
			snprintf(filePath,filePathLen - 1,"%s/",sp->rootPath);
		}else{
			strcpy(filePath,sp->rootPath);
		}

		if(type == ORIG_FILE){
			snprintf(filePath + rootLength ,filePathLen - 1,"%s",sp->fileName);
		}
		else if(type == INDEX_FILE){
			snprintf(filePath + rootLength ,filePathLen - 1,"%s.idx",sp->fileName);
		}else if(type == DATA_FILE){
			snprintf(filePath + rootLength ,filePathLen - 1,"%s.dat",sp->fileName);
		}

		return 1;

}

int getFile(int type,SysParam * sp,FILE ** fileVar){
	char filePath[1024];
	getFilePath(type , sp,  filePath,1024);
	*fileVar=fopen(filePath,"r");
	if(*fileVar == 0){
		return 0;
	}else{
		return 1;
	}
}

