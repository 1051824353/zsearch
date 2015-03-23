#ifndef _FILEUTIL_H_
#define _FILEUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sysHeader.h>

#define ORIG_FILE 1
#define DATA_FILE 2
#define INDEX_FILE 3

int getFilePath(int type,SysParam *sp,char * filePath,int filePathLen);

#endif
