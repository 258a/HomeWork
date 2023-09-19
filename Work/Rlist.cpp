#include <stdio.h>
#include <stdlib.h>
struct node
{//链表结点类型，包含一个存放整型数据的 data 成员，和一个指向下一个结点的next成员
    int data ;
    struct node *next ;   
};

//第一关代码
struct node *createRlist()
{//函数功能：创建一个有一个空循环链表，返回值为头指针
    struct node *head ;
    head=(struct node*)malloc(sizeof(struct node));
    head->next=head;
    return head;
}


struct node * insertOrder(struct node *list, int insData)
{
 //在单向递增有序的循环链表（表头指针list）中插入数据元素insData，使之依然有序 。返回值是头指针
    struct node *newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data=insData;
    if(list->next==NULL){
        list->next=newNode;
        newNode->next=list;
        return list;
    }
    struct node *prev=list;
    struct node *curr=list->next;
    while(curr!=list&&curr->data<insData){
        prev=curr;
        curr=curr->next;
    }
    newNode->next=curr;
    prev->next=newNode;
    return list;
}

int deleteData(struct node  *list, int delData)
{
    //在单向递增有序循环链表（表头指针list）中删除所有值为delData的结点,返回值为删除结点的个数
    int cnt=0;
    struct node *prev=list;
    struct node *curr=list->next;
    while(curr!=list){
        if(curr->data==delData){
            struct node *temp=curr;
            prev->next=curr->next;
            curr=curr->next;
            free(temp);
            cnt++;
        }
        else{
            prev=curr;
            curr=curr->next;
        }
    }
    return cnt;
}

void printRlist(struct node *list)
{
 //从链表第一个结点开始输出单向循环链表中各数据元素的值，每输出一个数据元素空一格
    struct node *p=list->next;
    while(p!=list){
        printf("%d ",p->data);
        p=p->next;
    }
}

int destroyRlist(struct node *list)
{
    //从第一个结点开始释放循环链表各结点占用的空间,返回值为最后一个结点的值
    int lastData = 0;
    if (list->next == list)
    {
        free(list);
        return lastData;
    }

    struct node *curr = list->next;
    struct node *next = curr->next;

    // 释放链表节点的空间
    while (curr != list)
    {
        lastData = curr->data;
        free(curr);
        curr = next;
        next = curr->next;
    }

    free(list);

    return lastData;
}

int main()
{
  struct node *head = createRlist();
  int num , data;
  scanf("%d",&num);
  for(int i=0;i<num;i++)
  {
     scanf("%d",&data);
     head = insertOrder(head, data);
      
  }
  printRlist(head);
  scanf("%d",&data);
  printf("\n%d ",deleteData(head,data));

  printf("\n%d ",destroyRlist(head));


  return 1;
}