#ifndef _TREELIST_H_
#define _TREELIST_H_

#define P_LEFT 1
#define P_RIGHT 2

typedef struct _TREE_NODE TreeNode;
struct _TREE_NODE{
	char data[1024];
	struct _TREE_NODE *parent;
	struct _TREE_NODE *left;
	struct _TREE_NODE *right;
	int pLR;
	int lastLeft;
};


typedef struct _TREE_LIST TreeList;
struct _TREE_LIST{
	int count;
	_TREE_NODE *entry;
	_TREE_NODE *start;
};


TreeList * initTreeList();
int insertSortTreeList(TreeList ** list,char * str);
int getTreeListCount(TreeList * list);
int destroyTreeList(TreeList * list);
char * getTreeListVal(TreeList * list,int index);
TreeNode * getNextTreeNode(TreeList * list,TreeNode * e);
#endif
