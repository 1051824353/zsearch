#ifndef _SYSPARAM_H_
#define _SYSPARAM_H_


typedef struct _SYS_PARAM SysParam;

struct _SYS_PARAM{
	int opt;
	char rootPath[256];
	char fileName[128];
	char filePath[512];
	char fileIndexPath[512];
	char fileDataPath[512];
	char grepChar[512];
};

#define CREATE_INDEX 0
#define FIND_DATA 1
#endif
