#include <stdio.h>
#include <stdlib.h>

/*哈希结构*/
struct hashTable
{
  int *element;//存放键值的连续空间起始地址
  int maxNum;// 哈希表长度 
  int curNum;//当前哈希表已有数据元素 
};

struct node
{
  int data ;
  struct node *next;
};

struct hashTable_link
{
  struct node *element;
  int maxNum;// 哈希表长度  
};

/*第一关*/
//初始化一个哈希表，能满足线性探测再散列处理冲突法使用，初始化哈希表元素均为-1，表示该位置为空，可插入
struct hashTable* initHashTable_linear()
{
  int maxNum=10;
  struct hashTable* table=(struct hashTable*)malloc(sizeof(struct hashTable));
  table->element=(int*)malloc(sizeof(int)*maxNum);
  if(!(table->element))
    return table;
  table->maxNum=maxNum;
  table->curNum=0;
  for(int i=0;i<maxNum;i++){
    table->element[i]=-1;
  }
  return table;
}

//初始化一个哈希表，能满足拉链法处理冲突法使用。初始化哈希表元素为0，用于计算该条链中数据个数，在插入时增加
struct hashTable_link * initHashTable_link()
{
  int maxNum=10;
  struct hashTable_link *table=(struct hashTable_link*)malloc(sizeof(struct hashTable_link));
  table->element=(struct node*)malloc(sizeof(struct node)*maxNum);
  table->maxNum=maxNum;
  for(int i=0;i<maxNum;i++){
    table->element[i].data=0;
    table->element[i].next=NULL;
  }
  return table;
}

/*第二关*/
//输出线性探测再散列法构建的哈希表,从下标为0的元素开始输出，每输出一个数据空一格
void printHashTable(struct hashTable *h)
{
  for(int i=0;i<h->maxNum;i++){
    printf("%d ",h->element[i]);
  }
}



/*第三关*/
//哈希函数，h(key) = (key*3) %  7
int hashFun(int key)
{
  return (key*3)%7;
}

//函数功能：计算key的哈希地址，若发生冲突，则使用线性探测再散列的方法查找合适的插入位置下标，并返回该下标
int findPos(struct hashTable *h , int key)
{
  int hkey=hashFun(key);
  while(h->element[hkey]!=-1){
    hkey=(hkey+1)%h->maxNum;
  }
  h->curNum++;
  return hkey;
}

//插入键值函数,若哈希表空间已满，则返回-1，否则返回插入位置下标
int insertKey(struct hashTable *h , int key)
{
  if(h->curNum==h->maxNum)
    return -1;
  int pos=findPos(h,key);
  h->element[pos]=key;
  return pos;
}


// //第一关主函数
// int main( )
// {
//   struct hashTable *h = initHashTable_linear();
//   printf("%d\n",h->maxNum);
//  for(int i=0;i<h->maxNum;i++)
//    printf("%d ",h->element[i]);
// printf("\n");   
//  struct hashTable_link *h1 = initHashTable_link(); 
//  printf("%d\n",h1->maxNum);
//  for(int i=0;i<h1->maxNum;i++)
//    printf("%d ",h1->element[i].data);
// }


// //第二关主函数
// #include "../hash.h"

// int main( )
// {
//   struct hashTable *h = initHashTable_linear();
//   //printf("%d\n",h->maxNum);
//  printHashTable(h);
 
// }


// 第三关主函数
// int main( )
// {
//   struct hashTable *h = initHashTable_linear();
//   int key;
//   for(int i=0;i<7;i++)
//   {
//    scanf("%d",&key);
//    insertKey(h,key);
//    }
//  printHashTable(h);
//  }