#include <stdio.h>
#include <stdlib.h>
/*----------------*/
// 若采取顺序存储结构，集合最多存放的元素个数，可自定义

struct SetNode // 若采用链式存储结构，则头结点不存储集合元素，存储集合中元素的个数，且数据成员命名为info
// 若采用顺序存储结构，则应有成员变量记录当前集合中数据元素个数，且该成员命名为info
{
    int info;
    struct SetNode *next;
};
typedef struct SetNode *Set;

void printSet(Set A)
{
    // 根据自定义数据结构，请先完成本函数，逐个输出集合元素，以一个空格为分界，最后一个元素输出后，追加输出一个换行符
    A = A->next;
    while (A != NULL)
    {
        printf("%d", A->info);
        if (A != NULL)
            printf(" ");
        A = A->next;
    }
    printf("\n");
}

// 第1关，创建一个空集合
Set createEmptySet()
{
    /*----------------*/
    Set A=(Set)malloc(sizeof(struct SetNode));
    A->next=NULL;
    A->info=0;
    return A;
    /*----------------*/
}

// 第2关，向集合中插入元素
void insert(int data, Set A)
{
    /*----------------*/
    if(A==NULL){
        Set p=(Set)malloc(sizeof(struct SetNode));
        p->info=data;
        p->next=NULL;
        A->next=p;
        A->info++;
    }
    else{
        Set p=A;
        Set q=A->next;
        while(q!=NULL){
            if(q->info==data){
                return;
            }
            else if(q->info>data){
                Set newnode=(Set)malloc(sizeof(struct SetNode));
                newnode->info=data;
                newnode->next=q;
                p->next=newnode;
                A->info++;
                return;
            }
            p=q;
            q=q->next;
        }
        Set newnode=(Set)malloc(sizeof(struct SetNode));
        newnode->info=data;
        newnode->next=NULL;
        p->next=newnode;
        A->info++;
        return;
    }
}

// 第3关，判断数据元素是否属于集合
int member(int data, Set A)
{
    /*----------------*/
    if(A->next==NULL)
        return 0;
    Set p=A->next;
    while(p){
        if(p->info==data)
            return 1;
        else
            p=p->next;
    }
    return 0;
}

// 第4关，从集合A中删除指定数据元素，返回集合
Set delete(int data, Set A)
{
    /*----------------*/
    if(A->next==NULL){
        return A;
    }
    Set p=A;
    Set q=A->next;
    while(q){
        if(q->info==data){
            p->next=q->next;
            free(q);
            A->info--;
            return A;
        }
        p=q;
        q=q->next;
    }
    return A;
}

// 第5关，求集合A,B的并集
void Union(Set A, Set B, Set C)
{
    /*----------------*/
    Set p=A->next;
    while(p!=NULL){
        insert(p->info,C);
        p=p->next;
    }
    p=B->next;
    while(p!=NULL){
        if(!member(p->info,C)){
            insert(p->info,C);
        }
        p=p->next;
    }
    return;
}

// 第6关，求集合A,B的交集
void intersect(Set A, Set B, Set C)
{
    /*----------------*/
    Set p=A->next;
    while(p!=NULL){
        if(member(p->info,B)){
            insert(p->info,C);
        }
        p=p->next;
    }
    return;
}

// 第7关，求集合A,B的差集
void difference(Set A, Set B, Set C)
{
    /*----------------*/
    Set p=A->next;
    while(p!=NULL){
        if(!member(p->info,B)){
            insert(p->info,C);
        }
        p=p->next;
    }
}
