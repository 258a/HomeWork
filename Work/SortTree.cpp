#include <stdio.h>
#include <stdlib.h>
//数据结构定义
struct node
{
    int data ;
    struct node *lchild ,*rchild ;
};

typedef struct node *pTree;
/*第一关*/


/*1.创建一个二叉树结点,值为element*/ 
pTree createTreeNode(int element)
{
    pTree T=(pTree)malloc(sizeof(struct node));
    T->data=element;
    T->lchild=NULL;
    T->rchild=NULL;
    return T;
}

/*2.在二叉排序树中插入一个数据元素,若二叉树为空，则新建根节点*/
pTree insertData(int x , pTree T)
{
    if(T==NULL){
        T=createTreeNode(x);
        return T;
    }
    if(x<T->data){
        T->lchild=insertData(x,T->lchild);
        return T;
    }
    if(x>T->data){
        T->rchild=insertData(x,T->rchild);
        return T;
    }
    return T;
}

/*3.先序遍历和中序遍历函数*/
void preOrder( pTree T)
{
    if(T==NULL) return;
    printf("%d ",T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}
void inOrder( pTree T)
{
    if(T==NULL) return;
    inOrder(T->lchild);
    printf("%d ",T->data);
    inOrder(T->rchild);
}


/*第二关*/
/*1.在二叉排序树T中查找最小值，返回该结点*/
pTree findMin(pTree T)
{
    if(T==NULL) return NULL;
    if(T->lchild==NULL) return T;
    return findMin(T->lchild);
}

/*2.在二叉排序树T中查找最大值，返回该结点*/
pTree findMax(pTree T)
{
    if(T==NULL) return NULL;
    if(T->rchild==NULL) return T;
    return findMax(T->rchild);
}


/*3.在二叉排序树T中查找指定数据元素，若未找到，则返回NULL*/
pTree findData(pTree T, int element)
{
    if(T==NULL) return NULL;
    if(T->data==element) return T;
    if(T->data>element) return findData(T->lchild,element);
    if(T->data<element) return findData(T->rchild,element);
    return NULL;
}

/*第三关*/
/*在二叉排序树T中删除指定元素的结点,若删除成功则返回该结点，否则返回NULL*/
pTree deleteData(pTree T,int element)
{
    if(T==NULL) return NULL;
    if(T->data==element)
    {
        if(T->lchild==NULL&&T->rchild==NULL) return NULL;
        if(T->lchild==NULL) return T->rchild;
        if(T->rchild==NULL) return T->lchild;
        pTree temp=findMin(T->rchild);
        T->data=temp->data;
        T->rchild=deleteData(T->rchild,temp->data);
        return T;
    }
    if(T->data>element) T->lchild=deleteData(T->lchild,element);
    if(T->data<element) T->rchild=deleteData(T->rchild,element);
return T;
}



