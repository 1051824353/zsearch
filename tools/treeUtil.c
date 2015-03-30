#include "treeUtil.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


TreeList * initTreeList(){
	TreeList *list=(TreeList *)MALLOC_OBJ(sizeof(TreeList));
	if(!list)
		return 0;
	list->count=0;
	list->entry=NULL;
	list->start = NULL;
	return list;
}

TreeNode * getLastLeft(TreeNode * e){
	if(e == NULL){
		return NULL;
	}
	while(e->left){
		e = e->left;
	}
	return e;
}

TreeNode * getLastVal(TreeNode * e){
	if(e == NULL ){
		return NULL;
	}
	if(e->right == NULL){
		return e;
	}
	TreeNode * tr = e->right;
	TreeNode * tp = getLastLeft(tr);
	return tp;
	/*if(tr == tp){
		return tr;
	}
	return getLastVal(tp);*/
}


TreeNode * getTreeNode(TreeList * list,int index){
	int num = 0;
	TreeList *l = list;
	TreeNode *e = l->start;
	TreeNode *b = e;
	while(e){
		if(index == num){
			return e;
		}
		b = e;
		e = getLastVal(b);
		if(e == b){
			while(1){
				if(b->pLR == P_LEFT && b->parent){
					e = e->parent;
					b = e;
				}else{
					break;
				}
			}
			e = e->parent;
		}
		++num;
	}
	return NULL;

}


char * getTreeListVal(TreeList * list,int index){
	TreeNode * e = getTreeNode(list,index);
	return e->data;
}

TreeNode * getNextTreeNode(TreeList * list,TreeNode * e){
	if(e == NULL){
		return list->start;
	}
	
	TreeNode *b = e;
	e = getLastVal(b);
	if(e == b){
		while(1){
			if(b->pLR == P_LEFT && b->parent){
				e = e->parent;
				b = e;
			}else{
				break;
			}
		}
		if(e->parent){
			e = e->parent;
		}
	}
	return e;

}

int getTreeListCount(TreeList * list){
	if(list == NULL){
		return 0;
	}else{
		return list->count;
	}
}

int leftRotate(TreeList **list){
	TreeList * l = *list;
	TreeNode * e = l->entry;
	if(e->left->right){
			
	}else{
		l->entry = e->left;
		e->parent = e->left;
		e->left->right = e;
		e->left->parent = NULL;
		e->left = NULL;
		e->pLR = P_LEFT;
	}
	return 1;
}

int rightRotate(TreeList **list){
	TreeList * l = *list;
	TreeNode * e = l->entry;
	if(e->right->left){
	
	}else{
		l->entry = e->right;
		e->parent = e->right;
		e->right->left = e;
		e->right->parent = NULL;
		e->right = NULL;
		e->pLR = P_RIGHT;
	}
	return 1;
}

int insertSortTreeList(TreeList ** list,char * str){
	if(*list == NULL){
		*list = initTreeList();
		TreeNode * add=(TreeNode *)MALLOC_OBJ(sizeof(TreeNode));
		(*list)->entry = add;
		(*list)->start = add;
		strcpy(add->data,str);
		add->parent = NULL;
		add->left = NULL;
		add->right = NULL;
		add->pLR = 0;
		add->lastLeft = 1;
		(*list)->count++;
		return 1;
	}
	TreeNode * add=(TreeNode *)MALLOC_OBJ(sizeof(TreeNode));
	strcpy(add->data,str);
	add->pLR = 0;
	add->lastLeft = 0;

	TreeList * l = *list;
	TreeNode * e = l->entry;
	int rotateLable = 0;
	while(e){
		if(strcasecmp(e->data,str) > 0){
			if(e->left == NULL){
				e->left = add;
				add->parent = e;
				add->pLR = P_RIGHT;
				if(e->lastLeft){
					e->lastLeft = 0;
					add->lastLeft = 1;
					l->start = add;		
				}
				break;
			}else{
				e = e->left	;
				if(rotateLable == 0 && l->count % 2 ==0) {
					rotateLable = 1;
				}
			}
		}else if(strcasecmp(e->data,str) == 0){
			return 1;
		}else{
			if(e->right == NULL){
				e->right = add;
				add->parent = e;
				add->pLR = P_LEFT;
				break;
			}else{
				e = e->right;
				if(rotateLable == 0  && l->count % 2 ==0){
					rotateLable = 2;
				}
			}
		}
	}
	if(rotateLable == 1){
		leftRotate(list);
	}else if(rotateLable == 2){
		rightRotate(list);
	}
	l->count++;
	return 1;
}

int removeTreeList(TreeList * list,int index){
	if(list == NULL){
		return 0;
	}
	TreeNode * e = getTreeNode(list,index);
	FREE_OBJ(e);
	return 1;
}

int destroyTreeList(TreeList * list){
	if(list == NULL){
		return 0;
	}
	int count = getTreeListCount(list);
	for(int i = 0;i < count;i++){
		removeTreeList(list,i);
	}
	FREE_OBJ(list);
	list = NULL;
	return 1;
}

