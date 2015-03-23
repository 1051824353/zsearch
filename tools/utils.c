#include <string.h>
#include "utils.h"
#include <iconv.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

int mkdir_ext(char *sPath,int mode,int nIsPath)
{

	char *p=sPath;

	if (sPath==NULL || *sPath==0) return -1;

	while (*p) 
	{    
		if (*p=='/' && p>sPath)
		{    
			*p=0;
			mkdir(sPath,mode);
			*p='/';
		}    
		p++; 

	}    
	if (nIsPath==1) 
	{    
		//如果为/a/b这样的形势，而且指明为路径名，则创建/a/b/，否则仅创建/a
		if (*(p-1)!='/') mkdir(sPath,mode);
	}    
	return 0;
}

int itostr( int i,char * des){
	sprintf(des, "%d", i);
	return 1;
}

int itLength(int i){
	int len = 0;
	int t = i;
	for(;;){
		++len;
		t = t /10;
		if(t < 1){
			return len;
		}
	}
	return 0;
}

int indexof(char * str,char * val){
	int strLength = strlen(str);
	int valLength = strlen(val);
	for(int i = 0; i < strLength ; i++){
		if(str[i] == val[0]){
			for(int j = 0; j < valLength ; j++){
				if(str[i + j ] == val[j]){
					if(j == valLength - 1){
						return i;
					}
				}else{
					break;
				}
			}
		}
	}
	return -1;
}

int lastindexof(char * str,char * val){
	int strLength = strlen(str);
	return lastnindexof(str,strLength,val);
}

int lastnindexof(char * str,int strLen,char * val){
	int strLength = strLen;
	int valLength = strlen(val);
	for(int i = strLength -1; i >= 0 ; i--){
		if(str[i] == val[valLength - 1]){
			for(int j = valLength - 1; j >=0 ; j--){
				if(str[i - valLength + j + 1 ] == val[j]){
					if(j == 0){
						return i - valLength + j + 1;
					}
				}else{
					break;
				}
			}
		}
	}
	return -1;
}

char * subfirst(char * str,char * val){
	int strLength = strlen(str);
	
	char * des = (char *)MALLOC_OBJ(strLength + 1);
	memset(des,0,strLength + 1);
	strncpy(des,str,strLength+1);

	int valLength = strlen(val);
	for(int i = 0; i < strLength ; i++){
		if(str[i] == val[0]){
			for(int j = 0; j < valLength ; j++){
				if(str[i + j ] == val[j]){
					if(j == valLength - 1){
						des[i] = 0;
						return des;
					}
				}else{
					break;
				}
			}
		}
	}
	FREE_OBJ(des);
	return 0;
}
int isipv4(char *p,size_t nDomainLen){
	//判断一个字符串是否为IPv4的格式
	unsigned int  i = 0,j=0;
	int a=0,b=0,c=0,d=0;
	//j记录.号的个数
	if (nDomainLen>15) return 0;
	
	for (i = 0; i < nDomainLen; i++) 
	{
		if (IS_INTEGER(p[i])) continue;
		if (p[i]=='.' && i>0 && i<(nDomainLen-1) && IS_INTEGER(p[i+1])) 
		{
			j++;
			continue;
		}
		
		return 0;
	}
	
	if (j==3) 
	{
		sscanf(p,"%d.%d.%d.%d",&a,&b,&c,&d);
		if (a>=0 && a<=255 && b>=0 && b<=255 && c>=0 && c<=255 && d>=0 && d<=255) return 1;
		else return 0;
	}
	else return 0;
}

unsigned char XOR(unsigned char c1,unsigned char c2){
	unsigned char nonC1,nonC2;
	nonC1=255-c1;
	nonC2=255-c2;
	return ((c1 & nonC2) | (c2 & nonC1));
}

int addBeforeStr(char * str,char * before,char * out){
	int strSize = strlen(str);
	int beforeSize = strlen(before);
	char tmp[strSize + beforeSize +1];
	strcpy(tmp,before);
	strcpy(tmp+beforeSize,str);
	strcpy(str,tmp);
	tmp[strSize + beforeSize] = 0;
	strcpy(out,tmp);
	return 1; 
}

int addLastStr(char * str,char * last,char *out){
	int strSize = strlen(str);
	int lastSize = strlen(last);
	char tmp[strSize + lastSize +1];
	strcpy(tmp,str);
	strcpy(tmp,last);
	strcpy(out,tmp);
	return 1;
}

int getTimeStdNoQuot(char * varStr,int size){
	time_t now;
	time(&now);
	struct tm tnow;
	localtime_r(&now,&tnow);
	snprintf(varStr,size,"%04d-%02d-%02d %02d:%02d:%02d",tnow.tm_year+1900,tnow.tm_mon+1,tnow.tm_mday,tnow.tm_hour,tnow.tm_min,tnow.tm_sec);
	return 1;
}

int getTimeStd(char * varStr,int size){
	time_t now;
	time(&now);
	struct tm tnow;
	localtime_r(&now,&tnow);
	snprintf(varStr,size,"\"%04d-%02d-%02d %02d:%02d:%02d\"",tnow.tm_year+1900,tnow.tm_mon+1,tnow.tm_mday,tnow.tm_hour,tnow.tm_min,tnow.tm_sec);
	return 1;
}
/*
int getTimeStr(char * varStr){
	char sDayOfWeek[17],sMon[17];
	int nDay=0,nHour=0,nMin=0,nSec=0,nYear=0;
	time_t tNow;
	time(&tNow);
	char tmpStr[256];
	memset(tmpStr,0,256);
	snprintf(tmpStr,255,"%s",ctime(&tNow));
	sscanf(tmpStr,"%s %s %d %d:%d:%d %d",sDayOfWeek,sMon,&nDay,&nHour,&nMin,&nSec,&nYear);
	sprintf(varStr,"%s, %02d %s %04d %02d:%02d:%02d",sDayOfWeek,nDay,sMon,nYear,nHour,nMin,nSec);
	return 1;
}
*/
int getTimeStr(char * varStr){
	time_t now;
	struct tm tm_now;
	time(&now);
	localtime_r(&now,&tm_now);
	strftime(varStr, 200, "%a, %d %b %Y %H:%M:%S %z", &tm_now);
	return 1;
}



int getChTimeStr(char * varStr){
	time_t tNow;
	struct tm pMyTm;
	
	time(&tNow);
	localtime_r(&tNow, &pMyTm);

	sprintf(varStr,"%04d年%02d月%02d日",pMyTm.tm_year+1900,pMyTm.tm_mon+1,pMyTm.tm_mday);
	return 1;
}

int getChDetailTimeStr(char * varStr){
	time_t tNow;
	struct tm pMyTm;

	time(&tNow);
	localtime_r(&tNow, &pMyTm);

	sprintf(varStr,"%04d年%02d月%02d日 %02d时%02d分%02d秒",pMyTm.tm_year+1900,pMyTm.tm_mon+1,pMyTm.tm_mday,pMyTm.tm_hour,pMyTm.tm_min,pMyTm.tm_sec);
	return 1;
}

int CalExpE(char *sExp, int szExp){
	char *p=NULL;
	if (szExp<1) return 0;
		
	p=(char *)MALLOC_OBJ(szExp+1);
	if (p==NULL) return 0;
	memcpy(p,sExp,szExp);
	p[szExp]=0;
	
	int midIndex = indexof(sExp ,(char *)",");

	char first[256];
   	memset(first,0,256);	
	strncpy(first,sExp + 2,midIndex - 4);
	char last[256];
	memset(last,0,256);
	strncpy(last,sExp + midIndex + 1 ,strlen(sExp) - midIndex - 2);

	if (strcmp(first, last) == 0){
		return 1;
	}
	else{
		return 0;
	}
	return 0;
}
/**
  x 中包含 y中的值
  **/
int CalExpX(char *sExp, int szExp){
	char *buf=NULL;
	char *p=NULL;
	int *pIdx=NULL;
	
	if (sExp==NULL) return 0;
	if (szExp<1) return 0;
		
	buf=(char *)MALLOC_OBJ(szExp+1);
	if (buf==NULL) return 0;
	memcpy(buf,sExp,szExp);
	buf[szExp]=0;
	
	p = strstr(buf, ",");
	if( p != NULL && p > buf && p+1 != NULL ){
		p[0] = '\0';
		char *tmp = strstr(buf, p+1);
		if( tmp != NULL){
			FREE_OBJ(buf);
			FREE_OBJ(pIdx);
			return 1;
		}
		else
		{
			FREE_OBJ(buf);
			FREE_OBJ(pIdx);
			return 0;
		}
	}
	
	FREE_OBJ(p);
	FREE_OBJ(pIdx);
	return 0;
}
/**
	y 中包含 x中的值
  **/
int CalExpI(char *sExp, int szExp){
	char *buf=NULL;
	char *p=NULL;
	int *pIdx=NULL;
	
	if (sExp==NULL) return 0;
	if (szExp<1) return 0;
		
	buf=(char *)MALLOC_OBJ(szExp+1);
	if (buf==NULL) return 0;
	memcpy(buf,sExp,szExp);
	buf[szExp]=0;
	
	p = strstr(buf, ",");
	if( p != NULL && p > buf && p+1 != NULL ){
		p[0] = '\0';
		char *tmp = strstr(p+1, buf);
		if( tmp != NULL){
			FREE_OBJ(buf);
			FREE_OBJ(pIdx);
			return 1;
		}
		else
		{
			FREE_OBJ(buf);
			FREE_OBJ(pIdx);
			return 0;
		}
	}

	FREE_OBJ(buf);
	FREE_OBJ(pIdx);
	return 0;
}
int calExp(char *sExp,int szExp){
	if (szExp<=0) return 0;
	if (sExp[0]=='~' && (sExp[1]=='E' || sExp[1]=='I' || sExp[1]=='X') && sExp[2]=='(' && sExp[strlen(sExp)-1]==')') 
	{    
		if (sExp[1]=='E') return 1-CalExpE(sExp+3,szExp-4);        
		if (sExp[1]=='X') return 1-CalExpX(sExp+3,szExp-4);
		if (sExp[1]=='I') return 1-CalExpI(sExp+3,szExp-4);
	}    
	if (sExp[0]=='E' && sExp[1]=='(' && sExp[strlen(sExp)-1]==')') return CalExpE(sExp+2,szExp-3);
	if (sExp[0]=='I' && sExp[1]=='(' && sExp[strlen(sExp)-1]==')') return CalExpI(sExp+2,szExp-3);
	if (sExp[0]=='X' && sExp[1]=='(' && sExp[strlen(sExp)-1]==')') return CalExpX(sExp+2,szExp-3);
	if (sExp[0]=='~' && sExp[1]=='(' && sExp[strlen(sExp)-1]==')') return 1-calExp(sExp+2,szExp-3);
	return 0;
}

int replaceallstr(char *str,char *from,char *to,char *des){
	if( !str){
	        return 0;
	}   
	strcpy(des,str);
	if( !from || !to ){
		return 1;
	}
	int desLen = strlen(des);
	int fromLen = strlen(from);
	int toLen = strlen(to);
	for(int i =0 ;i < desLen  ;i++){
		if(strncasecmp(des+i,from,fromLen) == 0){
			replacestr(des,from,to,des);
			desLen += toLen - fromLen;
		}
	}
	return 1;

}
int replacestr( char *str, char *from, char *to,char * des ){
	if( !str){
		return 0;
	}
	if( !from || !to ){
		strcpy(des,str);
		return 1;
	}
	char *retstr = NULL;
	char *p = strstr( str, from);
	int pos = 0;
	if( NULL != p ){
		pos = p - str;
		if( pos > 0 && pos < (int)strlen(str) ){
			retstr = (char*)MALLOC_OBJ( strlen(str) - strlen(from) + strlen(to) + 1);
			memset(retstr, 0, strlen(str) - strlen(from) + strlen(to) );
			strncat( retstr, str, pos);
			strncat( retstr+pos, to, strlen(to));
			strncat( retstr+pos+strlen(to), p+strlen(from), strlen(str)-pos-strlen(from) );
			strcpy(des,retstr);
			FREE_OBJ(retstr);
		}
		else
			strcpy(des,str);
	}
	else{
		strcpy(des,str);
	}
	return 1;
}


int replace(char * str,char old,char n){
	int strl = strlen(str);
	for(int i=0;i<strl;i++){
		if(str[i] == old){
			str[i] = n;
		}
	}
	return 1;
}

int stolower(char *src,char * des){
	strcpy(des,src);
	while(*des != '\0')
	{
		if(64 < *des && *des < 91)//a是65，z是90
		{
			*des = (*des+32);
		}
		des++;
	}
	return 1;
}
void trimCrlf(char *sLine)
{
	int n;
	n=strlen(sLine)-1;
	while (n>0 && (sLine[n]=='\r' ||  sLine[n]=='\n'))
	{
		sLine[n]=0;n--;
	}
}

void trimRight(char *sLine, int nLength){
	int n,i;
	n = strlen(sLine)-1;
	n = (n<nLength)? n : nLength;
	i = n;
	if( i>0 )
	{
		while( i>=0 && (sLine[i]=='\t' || sLine[i]==' ' || sLine[i]=='\n' || sLine[i]=='\r'))
		{
			i--;
		}
		sLine[i+1]=0;
	}
	return;
}
void trimQuotes(char *sLine, int nLength){
	trimLeft(sLine,nLength);
	trimRight(sLine,nLength);
	if(sLine[0] == '\"' || sLine[0] == '\''){
		for(int i =0 ;i < nLength - 1 ;i++){
			sLine[i] = sLine[i + 1];
		}
		sLine[nLength - 1] = 0;
	}
	int lineLength = strlen(sLine) - 1;
	if(sLine[lineLength]== '\"' || sLine[lineLength] == '\'' ){
		sLine[lineLength] = 0;	
	}
	return;

}
void trimLeft(char *sLine, int nLength){
	int n,i,j;
	n = strlen(sLine);
	n = (n<nLength)? n : nLength;
	i = 0;
	if( i<n && n>0 )
	{
		while( i<n && (sLine[i]=='\t' || sLine[i]==' '))
		{
			i++;
		}
		if( i>0 )
		{
			j = 0;
			while( j<=n-i )
			{
				sLine[j] = sLine[j+i];
				j++;
			}
			sLine[j]=0;
		}
	}
	return;
}
/*
   保存文件
	author: zhangyun
	data:	20121106
*/
int writefile( char *filename, char *buff){
	int ret = 0;
	FILE *fp = NULL;
	char tmp[1024];
	memset(tmp,0,1024);
	snprintf(tmp, SIZEOF_1(tmp), "%s", filename);
	mkdir_ext(filename, S_IRWXU|S_IRGRP|S_IROTH, 0);

	if((fp = fopen(tmp, "w"))==NULL)
	{
		return -1;
	}
	if(fwrite(buff, strlen(buff), 1, fp)!=1)
	   	ret = -2;
	if(fp)
		fclose(fp);
	return ret;
}

int isPidRunning(char * sPid){
	char sTmpFile[129];
	memset(sTmpFile,0,129);
	snprintf(sTmpFile,SIZEOF_1(sTmpFile),"/proc/%s/stat",sPid);
	FILE *f=fopen(sTmpFile,"r");
	if(f){
		fclose(f);
		return 1;
	}
	return 0;
}
int readCharItem(char *sLine,char *sItemName,char *pnValue){
	int lineLength = strlen(sLine);
	int itemLength = strlen(sItemName);
	for(int i =0;i < lineLength;i++){
		if(strncasecmp(sLine + i,sItemName,itemLength) == 0){
			sscanf(sLine+i+strlen(sItemName),"%s",pnValue);
			return 1;
		}
	}
	return 0;
}

int getLineCount(char * filePath){
	FILE *f = fopen(filePath,"r");
	int i = 0;
	char c = '\0';
	char tc = '\0';
	if(f){
		while ((c=fgetc(f))!=EOF){ 
			if(c=='\n')
				i++;
			tc = c;
		}
		if(tc != '\n'){
			i++;
		}
		fclose(f);
	}
	return i;
}
int readStrFile(char **content,FILE * f){
	char sLine[40960];
	int Len = 0;
	memset(sLine,0,40960);
	while (fgets(sLine,40960,f)!=0){
		int L=strlen(sLine);
		if (*content==NULL){ 
			*content = (char *)MALLOC_OBJ(L+1);
		}else{
			*content = (char *)REALLOC_OBJ(*content,Len+L+1);
		}   
		strncpy(*content+Len,sLine,L+1);
		Len+=L;
		memset(sLine,0,40960);
	}   
	return Len;	
}
int readByteFile(char **content,int *conLen,FILE * f){
	char sLine[40960];
	int Len = 0;
	int rLen = 0;
	memset(sLine,0,40960);
	while ((rLen = fread(sLine,1,40959,f)) > 0){
		if (*content==NULL){ 
			*content = (char *)MALLOC_OBJ(rLen+1);
		}else{
			*content = (char *)REALLOC_OBJ(*content,Len+rLen+1);
		}   
		memcpy(*content+Len,sLine,rLen);
		Len+=rLen;
		memset(sLine,0,40960);
	}   
	*conLen = Len;
	return 1;	

}
int readStrFileFirstMem(char * content , FILE * f){
	char sLine[40960];
	while (fgets(sLine,SIZEOF_1(sLine),f)!=0){
		strcat(content,sLine);
	}
	return 1;
}

int* splitRetInt(char * str,char dot,int * len){
	int *ret = NULL;
	int count = 0;
	int strL = strlen(str);
	int start = 0;
	char tmp[16];

	for(int i=0;i<strL;i++){
		if(str[i] == dot || i == strL-1){
			if(ret == NULL){
				ret = (int *)MALLOC_OBJ(sizeof(int));
			}else{
				ret = (int *)REALLOC_OBJ(ret,sizeof(int)*(count + 1));
			}
			memset(tmp,0,16);
			if(str[i] == dot){
				strncpy(tmp,str+start,i - start);
			}else{
				strncpy(tmp,str+start,i - start + 1);
			}
			if(IS_INTEGER(tmp[0])){
				ret[count] = atoi(tmp);
			}else{
				return NULL;	
			}
			++count;
			start = i + 1;
		}
	}
	*len = count;
	return ret;
}

int bubbleSort(int source[], int array_size){  
	int i, j;  
	int temp;  
	for (i = 0; i < array_size; i++)  
	{  
		for (j = 0; j < array_size - i - 1; j++)  
			if (source[j] > source[j + 1])  
			{  
				temp = source[j];  
				source[j] = source[j + 1];  
				source[j + 1] = temp;  
			}  
	}  
	return 1;  
}

char is_in_set(char c,char *set){
	int i=0;
	while (set[i]!=c && set[i]) i++;	
	return set[i];
}


int getRefNumIndex(char * idRef,int num){
	char rIdStr[16];
	memset(rIdStr,0,16);
	sprintf(rIdStr,"%d#",num);
	char * refSIndex = strstr(idRef,rIdStr);
	char * refIndex = subfirst(refSIndex+strlen(rIdStr) ,(char *)",");
	int attIndex = atoi(refIndex);
	FREE_OBJ(refIndex);
	return attIndex;
}
void cstrcpy(char * des,const char *src){
	if(src == NULL){
		return;
	}
	strcpy(des,src);
}
int catoi(const char * str){
	if(str == NULL){
		return 0;
	}
	return atoi(str);
}
int download(const char * url,char * filepath){
	int reTry = 1;
	int tryNum = 0;
	char sCommand[1025];
	while(reTry){
		reTry = 0;
		if(tryNum > 6){
			printf("try 6 fail [%s]\n",url);
			return 1;
		}
		if(tryNum > 3){
			sleep(1);
		}
		++tryNum;
		memset(sCommand,0,1025);
		snprintf(sCommand,SIZEOF_1(sCommand),"wget -U NoSuchBrowser/1.0 %s -O %s 2>&1",url,filepath);
		FILE *pCommand=popen(sCommand,"r");
		if (pCommand){
			while (fgets(sCommand,1024,pCommand) !=0 ){
				if(indexof(sCommand,(char *)"ERROR") > 0){
					reTry = 1;
					printf("download img fail [%s]\n",url);
					sleep(1);
					break;
				}
			}
			pclose(pCommand);
		}else{
			return 0;
		}
	}
	return 1;
}
int isImage(char *s)
{
	char *p;

	p=strrchr(s,'.');
	if (p){    
		p++;         
		if (strcasecmp(p,"gif")==0) return 1;
		if (strcasecmp(p,"bmp")==0) return 1;   
		if (strcasecmp(p,"jpg")==0) return 1;   
		if (strcasecmp(p,"jpeg")==0) return 1;           
		if (strcasecmp(p,"png")==0) return 1;   
		if (strcasecmp(p,"tif")==0) return 1;       
	}    
	return 0;
}
int getPathLastName(char * filePath,char * lastName){
	if(filePath == NULL){
		return -1;
	}
	int filePathLen = strlen(filePath);
	int i = 0;
	int isLastDirSign = 0;
	if(filePath[filePathLen - 1] == '/'){
		i = filePathLen - 2;
		isLastDirSign = 1;
	}else{
		i = filePathLen;
	}
	for(;i >= 0 ; i--){
		if(filePath[i] == '/'){
			i++;
			break;	
		}
	}
	int j = 0;
	for(; i < filePathLen  ; j ++,i++){
		lastName[j] = filePath[i];
	}
	if(isLastDirSign){
		lastName[j-1] = 0;	
	}
	return 1;
}
int convertCharset(const char *fCharset, const char *tCharset,char *str){
	if(strcasecmp(fCharset,tCharset) == 0 || strlen(str) == 0){
		return 1;
	}else{
		iconv_t c_pt;
		size_t lenin, lenout;
		int ret = -1;
		char *sin=str;
		lenin = strlen(str) + 1;
		lenout = lenin * 2;
		char *tstr = (char *)MALLOC_OBJ(lenout);
		char *sout=tstr;
		memset(tstr,0,lenout);
		if ((c_pt = iconv_open(tCharset, fCharset)) == (iconv_t)-1){
			FREE_OBJ(sout);
			return 0;
		}
		ret = iconv(c_pt, &sin, &lenin, &sout, &lenout);
		if (ret==-1) {
			printf("[Waring] Convert \"%s\" %d [%s] Fail!\n",str,errno,strerror(errno));
			FREE_OBJ(tstr);
			return 0;
		}

		if (c_pt!=(iconv_t)-1) iconv_close(c_pt);
		strcpy(str,tstr);
		FREE_OBJ(tstr);
		return 1;

	}

}
unsigned long get_file_size(const char *path){  
	unsigned long filesize = -1;      
	struct stat statbuff;  
	if(stat(path, &statbuff) < 0){  
		return filesize;  
	}else{  
		filesize = statbuff.st_size;  
	}  
	return filesize;  
}

