#ifndef _UTILS_H_
#define _UTILS_H_
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

//printf("%s:%d:%s:free(0x%lx,0x%lx):size(%d)\n", __FILE__, __LINE__, __func__, (unsigned long) ptr,(unsigned long)c,s );

#ifdef MCHECK 
#define MALLOC_OBJ(s) ({\
		void * c = malloc(s);\
		memset(c,0,s);\
		printf("%s:%d:%s:malloc(0x%lx):size(%d)\n", __FILE__, __LINE__, __func__, (unsigned long)c,s );\
		(c);\
		})
#else
#define MALLOC_OBJ(s) ({\
		void * c = malloc(s);\
		memset(c,0,s);\
		(c);\
		})
#endif

#ifdef MCHECK
#define REALLOC_OBJ(ptr,s) ({\
		void * c = realloc(ptr,s);\
		printf("%s:%d:%s:realloc(0x%lx,0x%lx):size(%d)\n", __FILE__, __LINE__, __func__, (unsigned long) ptr,(unsigned long)c,s );\
		(c);\
		})
#else
#define REALLOC_OBJ(ptr,s) ({\
		void * c = realloc(ptr,s);\
		(c);\
		})
#endif

#ifdef MCHECK
#define FREE_OBJ(c) if ((c)!=NULL) { \
	printf("%s:%d:%s:free(0x%lx)\n", __FILE__, __LINE__, __func__, (unsigned long)c );\
	free(c);c=NULL;\
}
#else
#define FREE_OBJ(c) if ((c)!=NULL) { \
	free(c);c=NULL;\
}
#endif

#define SIZEOF_1(c) ((signed)sizeof(c)-1)
#define IS_INTEGER(c) ( (c>='0' && c<='9') )

#define ENCA_GBK 1
#define ENCA_UTF8 2
#define ENCA_UNKOWN 0

typedef long long LONG64;

int itostr( int i,char * des);
int itLength(int i);
char * subfirst(char * str,char * val);
int indexof(char * str,char * val);
int lastindexof(char * str,char * val);
int lastnindexof(char * str,int strLen,char * val);
int mkdir_ext(char *sPath,int mode,int nIsPath);
int isipv4(char *p,size_t nDomainLen);
unsigned char XOR(unsigned char c1,unsigned char c2);
int encodeXorBase64(char *sEnc,int szEnc,char *sDecode,size_t szDecode,unsigned char *sKey);
int addBeforeStr(char * str,char * before,char * out);
int addLastStr(char * str,char * last,char * out);
int getTimeStdNoQuot(char * varStr,int size);
int getTimeStd(char * varStr,int size);
int getTimeStr(char * des);
//int getHeaderTimeStr(char * varStr);
int getChDetailTimeStr(char * des);
int getChTimeStr(char * des);
int calExp(char *sExp,int szExp);
int replacestr( char *str, char *from, char *to ,char * des);
int replace(char * str,char old,char n);
int stolower(char *src,char * des);
void trimRight(char *sLine, int nLength);
void trimLeft(char *sLine, int nLength);
void trimQuotes(char *sLine, int nLength);
void trimCrlf(char *sLine);
int writefile( char *filename, char *buff);
int isPidRunning(char * sPid);
int readCharItem(char *sLine,char *sItemName,char *pnValue);
int getLineCount(char * filePath);
int readStrFile(char **content,FILE * f);
int readByteFile(char **content,int * conLen,FILE * f);
int readStrFileFirstMem(char * content , FILE * f);
int* splitRetInt(char * str,char dot,int * len);
int bubbleSort(int source[], int array_size);
int getRefNumIndex(char * idRef,int num);
void cstrcpy(char * des,const char * src);
int catoi(const char * str);
int download(const char * url,char * filepath);
int isImage(char *s);
int getPathLastName(char * filePath,char * lastName);
int convertCharset(const char *fCharset, const char *tCharset,char *str);
unsigned long get_file_size(const char *path);
int replaceallstr(char *str,char *from,char *to,char *des);
