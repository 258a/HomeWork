#include <iostream>
using namespace std;

/*数据结构定义*/
typedef int DataType;
typedef struct
{
  DataType *data; // 用于存放待排序关键字的起始地址
  int NUM;        // 待排序关键字的个数
} SortObject;

typedef struct node // 用于表插入排序的数据结构
{
  DataType info;
  struct node *next;
} linkObject;

// 输出顺序表
void print(SortObject *p)
{
  for (int i = 0; i < p->NUM; i++)
    cout << p->data[i] << " ";
  cout << endl;
}

// 输出链表
void printLink(linkObject *Head)
{
  linkObject *p = Head->next;
  while (p)
  {
    cout << p->info << " ";
    p = p->next;
  }
  cout << endl;
}

/*第一关
此处请填写代码实现递增序进行直接插入排序,
 要求每趟排序后 调用print函数，输出关键字的排列情况*/
void insertSort(SortObject *Rec)
{
  cout << "the result of insertSort:\n";
  /*----begin------*/
  int tmp;
  int j;
  for (int i = 1; i < Rec->NUM; i++)
  {
    tmp = Rec->data[i];
    for (j = i - 1; j >= 0 && Rec->data[j] > tmp; j--)
    {
      Rec->data[j + 1] = Rec->data[j];
    }
    Rec->data[j + 1] = tmp;
    print(Rec);
  }
  /*-----end------*/
}

/*第二关
此处请填写代码实现递增序进行二分插入排序,

  实质是在已经有序的表中采用二分法查找插入位置
  要求每趟排序后 调用print函数，输出关键字的排列情况*/
void binInsertSort(SortObject *Rec)
{
  cout << "the result of binInsertSort:\n";
  /*----begin------*/
  for (int i = 1; i < Rec->NUM; i++)
  {
    if (Rec->data[i] < Rec->data[i - 1])
    {
      int left = 0;
      int right = i - 1;
      int n = Rec->data[i];
      while (left <= right)
      {
        int mid = (left + right) / 2;
        if (n < Rec->data[mid])
        {
          right = mid - 1;
        }
        else
        {
          left = mid + 1;
        }
      }
      for (int j = i - 1; j >= left; j--)
      {
        Rec->data[j + 1] = Rec->data[j];
      }
      Rec->data[left] = n;
    }
    print(Rec);
  }
  /*-----end------*/
}

/*第三关
此处请填写代码实现递增序进行表插入排序,
  返回值是关键字比较次数
  Head是表头结点，不存放数据，info是待插入数据
  要求每趟排序后 调用printLink函数，输出关键字的排列情况
  */
void listSort(linkObject *plist)
{
  cout << "the result of listSort:\n";
  /*----begin------*/
  if (plist == NULL || plist->next == NULL)
  {
    return;
  }
  linkObject *p = plist;
  linkObject *q = plist->next;
  linkObject *r = plist;
  r->next = NULL;
  while (q->next != NULL)
  {
    linkObject *p1 = p;
    linkObject *pre = NULL;
    while (p1 && q->info >= p1->info)
    {
      pre = p1;
      p1 = p1->next;
    }
    if (p1 == NULL)
    {
      r->next = q;
      q = q->next;
      r = r->next;
      r->next = NULL;
    }
    else if (pre == NULL)
    {
      linkObject *temp = q->next;
      q->next = p;
      p = q;
      q = temp;
    }
    else
    {
      pre->next = q;
      q = q->next;
      pre->next->next = p1;
    }
    plist = p;
    printLink(plist);
  }
  /*-----end------*/
}

/*第四关
此处请填写代码实现递增序进行冒泡排序,
 要求每趟排序后 调用print函数，输出关键字的排列情况
  */
void bubbleSort(SortObject *Rec)
{
  cout << "the result of bubbleSort:\n";
  /*----begin------*/
  for (int i = 0; i < Rec->NUM - 1; i++)
  {
    for (int j = 0; j < Rec->NUM - 1 - i; j++)
    {
      if (Rec->data[j] > Rec->data[j + 1])
      {
        swap(Rec->data[j], Rec->data[j + 1]);
      }
    }
    print(Rec);
  }
  /*-----end------*/
}

/*第五关
此处请填写代码实现递增序进行改进的冒泡排序,
 要求每趟排序后 调用print函数，输出关键字的排列情况
  */
void qbubbleSort(SortObject *Rec)
{
  cout << "the result of qbubbleSort:\n";
  /*----begin------*/
  int t = 0;
  for (int i = 0; i < Rec->NUM - 1; i++)
  {
    int flag = 0;
    for (int k = 0; k < Rec->NUM - 1; k++)
    {
      if (Rec->data[k] < Rec->data[k + 1])
      {
        flag++;
      }
      if (flag == Rec->NUM - 1)
      {
        if(t==0)
        print(Rec);
        return;
      }
    }
    for (int j = 0; j < Rec->NUM - 1 - i; j++)
    {
      if (Rec->data[j] > Rec->data[j + 1])
      {
        swap(Rec->data[j], Rec->data[j + 1]);
      }
    }
    print(Rec);
    t++;
  }
  /*-----end------*/
}

/*第六关
此处请填写代码实现递增序进行选择排序,
 要求每趟排序后 调用print函数，输出关键字的排列情况
  */
void selectSort(SortObject *Rec)
{
  cout << "the result of selectSort:\n";
  /*----begin------*/
  for(int i=0;i<Rec->NUM-1;i++){
    int min=i;
    for(int j=i+1;j<Rec->NUM;j++){
      if(Rec->data[j]<Rec->data[min]){
        min=j;
      }
    }
    if(min!=i){
      swap(Rec->data[i],Rec->data[min]);
    }
    print(Rec);
  }
  /*-----end------*/
}
