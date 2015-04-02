#ifndef _HASHLIST_H_
#define _HASHLIST_H_

#define HASH_SIZE 1000

#include "treeUtil.h"

typedef struct _HASH_LIST HashList;
struct _HASH_LIST{
	int count;
	int vaildTreeCount;
	TreeList * tree[HASH_SIZE];
};

int getHashCode();
HashList * initHashList();
int insertSortHashList(HashList ** list,char * str);
int getHashListCount(HashList * list);
int destroyHashList(HashList * list);
char * getHashListVal(HashList * list,int code);
int getHashListVaildCount(HashList *list);
#endif
