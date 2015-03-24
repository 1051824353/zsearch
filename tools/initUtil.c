#include "initUtil.h"
#include "sysHeader.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>

void initSysParam(SysParam * sp){
	sp->opt = 0;
	memset(sp->rootPath,0,256);
	memset(sp->fileName,0,128);
	memset(sp->filePath,0,512);
	memset(sp->fileIndexPath,0,512);
	memset(sp->fileDataPath,0,512);
	memset(sp->grepChar,0,512);
}
