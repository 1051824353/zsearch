#include "linkUtil.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


LinkList * initLinkList(){
	LinkList *list=(LinkList *)MALLOC_OBJ(sizeof(LinkList));
	if(!list)
		return 0;
	list->count=0;
	list->entry=NULL;
	return list;
}

char * getLinkListVal(LinkList * list,int index){
	int num = 0;
	LinkList *l = list;
	LinkEntry *e = l->entry;
	while(e){
		if(index == num){
			return (char *)e->data;
		}
		e = e->next;
		++num;
	}
	return NULL;
}

int containLinkList(LinkList * list,char * str){
	LinkList *l = list;
	LinkEntry *e = l->entry;
	while(e){
		if(strcasecmp(e->data,str) == 0){
			return 1;
		}
		e = e->next;
	}
	return 0;
}
int getLinkListCount(LinkList * list){
	if(list == NULL){
		return 0;
	}else{
		return list->count;
	}
}

int insertLinkList(LinkList ** list,char * str){
	if(*list == NULL){
		*list = initLinkList();
		LinkEntry * add=(LinkEntry *)MALLOC_OBJ(sizeof(LinkEntry));
		(*list)->entry = add;
		strcpy(add->data,str);
		(*list)->count++;
		return 1;
	}
	LinkList * l = *list;
	LinkEntry * e = l->entry;
	while(e->next){
		e = e->next;
	}
	LinkEntry * add=(LinkEntry *)MALLOC_OBJ(sizeof(LinkEntry));
	e->next = add;
	strcpy(add->data,str);
	l->count++;
	return 1;
}

int insertSortLinkList(LinkList ** list,char * str){
	if(*list == NULL){
		*list = initLinkList();
		LinkEntry * add=(LinkEntry *)MALLOC_OBJ(sizeof(LinkEntry));
		(*list)->entry = add;
		strcpy(add->data,str);
		(*list)->count++;
		return 1;
	}
	LinkEntry * add=(LinkEntry *)MALLOC_OBJ(sizeof(LinkEntry));
	strcpy(add->data,str);

	int insertOk = 0;
	LinkList * l = *list;
	LinkEntry * e = l->entry;
	LinkEntry * be = NULL;
	while(e){
		if(strcasecmp(e->data,str) > 0){
			if(e->front == NULL){
				l->entry = add;
			}else{
				add->front = e->front;
				e->front->next = add;	
			}
			add->next = e;
			e->front = add;
			insertOk = 1;
			break;
		}else if(strcasecmp(e->data,str) == 0){
			return 1;
		}
		be = e;
		e = e->next;
	}
	if(!insertOk){
		be->next = add;
		add->front = be;
	}
	l->count++;
	return 1;
}

int removeLinkList(LinkList * list,int index){
	int num = 0;
	LinkList * l = list;
	LinkEntry ** e = &l->entry;
	while(*e){
		LinkEntry * le = (*e)->next;
		if(index == num){
			FREE_OBJ(*e);
			*e = le;
			break;
		}
		*e = (*e)->next;
	}
	return 1;
}

int destroyLinkList(LinkList * list){
	if(list == NULL){
		return 0;
	}
	LinkEntry * e = list->entry;
	LinkEntry * te = NULL;
	while(e){
		te = e->next;
		FREE_OBJ(e);
		e = te;
	}
	FREE_OBJ(list);
	list = NULL;
	return 1;
}

