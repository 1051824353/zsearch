#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct _LinkEntry LinkEntry;
struct _LinkEntry{
	char data[1024];
	struct _LinkEntry *next;
	struct _LinkEntry *front;
};


typedef struct _LinkList LinkList;
struct _LinkList{
	int count;
	LinkEntry *entry;
};


LinkList * initLinkList();
char * getLinkListVal(LinkList * list,int index);
int insertLinkList(LinkList ** list,char * str);
int insertSortLinkList(LinkList ** list,char * str);
int getLinkListCount(LinkList * list);
int destroyLinkList(LinkList * list);
int containLinkList(LinkList * list,char * str);
#endif
