#include "treeUtil.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
TreeList * initHashList(){
	HashList *list=(TreeList *)MALLOC_OBJ(sizeof(HashList));
	if(!list)
		return 0;
	list->count=0;
	list->vaildTreeCount = 0;
	list->node=NULL;
	return list;
}

int getHashCode(char * str){
	int code = 0;
	int len = strlen(str);
	for(int i=0 ; i<len ; i++){
		code += str[i];
	}
	return code % HASH_SIZE;
}

int getHashListVaildCount(HashList *list){
	if(list == NULL){
		return 0;
	}else{
		return list->vaildTreeCount;
	}
}

int getHashListCount(HashList * list){
	if(list == NULL){
		return 0;
	}else{
		return list->count;
	}
}

TreeList * getHashTree(HashList * list,int index){
	if(str == NULL){
		return NULL;
	}
	if(index > HASH_SIZE || index <HASH_SIZE){
		return NULL;
	}
	HashList *l = list;
	return l->tree[index];
}

int insertHashList(HashList ** list,char * str){
	if(str == NULL){
		return -1;
	}
	HashList *l = *list;
	if(l == NULL){
		l = initHashList();
	}
	int code = getHashCode(str);
	if(l->tree[code] == NULL){
		l->vaildTreeCount++;
	}
	insertSortTreeList(l->tree[code],str);
	l->count++;
	return 1;
}


int destroyHashList(HashList * list){
	if(list == NULL){
		return 0;
	}
	for(int i=0 ; i<HASH_SIZE ; i++){
		TreeList * tree = l->tree[code];
		if(tree == NULL){
			return 0;
		}
		destroyTreeList(tree);
	}
	return 1;
}

*/
