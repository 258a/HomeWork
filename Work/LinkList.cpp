#include <iostream>
using namespace std;
// 第一关代码

struct node
{ // 此处填写代码，定义链表结点类型，包含一个存放整型数据的 成员，和一个指向下一个结点的成员
    int data;
    node *next;
};

struct node *mycreateList()
{ // 此处填写代码，创建一个只有一个头结点的空链表，头节点的数据域赋值为0，并将表头结点的地址返回
    node *head;
    head = new node;
    head->data = 0;
    head->next = NULL;
    return head;
}

// 第二关代码

void myinsertHead(struct node *&head, int insData)
{
    /*在此处完成任务，实现在head为表头d 链表的头插数据元素insData的功能*/
    // begin'
    // if (head->data == 0)
    // {
    //     head->data = insData;
    //     return;
    // }
    // struct node *newNode;
    // newNode = new node;
    // newNode->data = insData;
    // newNode->next = head;
    // head = newNode;
    struct node *p = new node;
    p->data = insData;
    p->next = head->next;
    head->next = p;
    head->data++;
    // end
}

void myinsertTail(struct node *head, int insData)
{
    /*在此处完成任务，在head为表头的单链表表尾插入数据元素insData*/
    // begin
    struct node *newNode;
    newNode = new node;
    newNode->data = insData;
    newNode->next = NULL;
    struct node *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode;
    // end
}

void myprintList(struct node *L)
{
    /*在此处完成任务，输出L为表头链表中的数据，每输出一个数据换一行*/
    // begin
    struct node *p = L;
    p = p->next;
    while (p->next != NULL)
    {
        cout << p->data << endl;
        p = p->next;
    }
    cout << p->data << endl;

    // end
}

// 第三关代码
int myfindPos(struct node *L, int pos)
{
    // 请在此处填入代码，实现在链表中查找第pos个结点的功能
    // begin
    if (pos < 1 || pos > 7)
    {
        return -1;
    }
    else
    {
        struct node *p = L;
        for (int i = 0; i < pos; i++)
        {
            p = p->next;
        }
        return p->data;
    }
    // end
}

int myfindKey(struct node *L, int key)
{
    // 请在此处填入代码，实现在链表中查找与key值相同的第一个结点的功能
    // begin
    struct node *p = L;
    int cnt = 0;
    while (L->next != NULL)
    {
        cnt++;
        L = L->next;
    }
    for (int i = 0; i < cnt; i++)
    {

        if (key == p->data)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
    // end
}

// 第四关代码
int mydeletePos(struct node *L, int pos)
{
    // 请在此处填入代码，实现在链表中删除第pos个结点的功能
    // begin
    node *p = L;
    node *q = L->next;
    node *r = L;
    node *ptr = L;
    int cnt = 0;
    while (r->next != NULL)
    {
        cnt++;
        r = r->next;
    }
    L->data = cnt;
    if (L == NULL)
    {
        return 0;
    }
    if (pos == 1)
    {
        node *temp = L;
        ptr = ptr->next;
        free(temp);
        L->data--;
        return 1;
    }
    int count = 1;
    while (q->next != NULL)
    {
        if (count == pos)
        {
            p->next = q->next;
            free(q);
            L->data--;
            return 1;
        }
        p = q;
        q = q->next;
        count++;
    }
    p->next = NULL;
    free(q);
    L->data--;
    return 1;
    // end
}

int mydeleteKey(struct node *L, int key)
{
    // 请在此处填入代码，实现在链表中删除与key值相同的第一个结点的功能
    // begin
    node *p = L;
    node *q = L->next;
    node *r = L;
    node *ptr = L;
    int cnt = 0;
    while (r->next != NULL)
    {
        cnt++;
        r = r->next;
    }
    L->data = cnt;
    if (L == NULL)
    {
        return 0;
    }
    if (ptr->data == key)
    {
        node *temp = L;
        ptr = ptr->next;
        free(temp);
        L->data--;
        return 1;
    }
    while (q->next != NULL)
    {
        if (q->data == key)
        {
            p->next = q->next;
            free(q);
            L->data--;
            return 1;
        }
        p = q;
        q = q->next;
    }
    return 0;
    // end
}

// 第五关代码
void reverseList_link(struct node *L)
{
    // 请在此处填入代码，实现链表逆置功能
    // begin
    struct node *p = L->next;
    struct node *q = NULL;
    L->next = NULL;
    while (p)
    {
        myinsertHead(L, p->data);
        q = p->next;
        delete p;
        p = q;
    }
    // end
}
