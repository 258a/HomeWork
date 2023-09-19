#include <stdio.h>
#include <stdlib.h>
struct node
{//链表结点类型，包含一个存放整型数据的 data 成员，和指向前驱和后继结点的指针
    int data ;
    struct node *llink, *rlink ;   
};

struct Hnode
{
    //双向链表头结点,有两个指针成员，分别指向双向链表的第一个结点和最后一个结点
    struct node *head, *tail;
};

//第二关代码
struct Hnode *createDlist()
{//函数功能：创建一个带头结点的双向链表，tail指向尾结点；head指针指向第一个结点，返回值是指向头结点的指针
    struct Hnode *list;
    list=(struct Hnode *)malloc(sizeof(struct Hnode));
    list->head=(struct node *)malloc(sizeof(struct node));
    list->tail=list->head;
    list->head->llink=NULL;
    list->head->rlink=NULL;
    return list;
}


void insertDlist(struct Hnode *list, int insData)
{
 //在双向链表的表头插入数据  
    struct node *newNode=(struct node *)malloc(sizeof(struct node));
    newNode->data=insData;
    newNode->llink=NULL;
    newNode->rlink=NULL;
    if(list->head==NULL){
        list->head=newNode;
        list->tail=newNode;
    }
    else{
        newNode->rlink=list->head;
        list->head->llink=newNode;
        list->head=newNode;
    }
}

int deleteData(struct Hnode  *list, int delData)
{
    //在双向链表中删除值为delData的第一个结点，若删除成功返回1，否则返回0
    struct node *prev=list->head;
    struct node *curr=list->head->rlink;
    while(curr!=list->tail){
        if(delData==curr->data){
            prev->rlink=curr->rlink;
            curr->rlink->llink=prev;
            free(curr);
            return 1;
        }
        else{
            prev=curr;
            curr=curr->rlink;
        }
    }
    return 0;
}

void printDlist(struct Hnode *list)
{
 //输出双向循环链表中各数据元素的值，每输出一个数据元素换行
    struct node *curr=list->head;
    while(curr!=list->tail){
        printf("%d\n",curr->data);
        curr=curr->rlink;
    }
}

int destroyDlist(struct Hnode *list)
{//释放双向链表占用的存储空间，释放所有结点,返回释放的结点数，不含list本身
    int cnt=0;
    struct node *curr=list->head;
    while(curr!=list->tail){
        struct node *temp=curr->rlink;
        free(curr);
        curr=temp;
        temp=temp->rlink;
        cnt++;
    }
    return cnt;
}