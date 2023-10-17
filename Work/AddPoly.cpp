#ifndef _LAB1_H_
#define _LAB1_H_
#include <iostream>
#include <stdio.h>

using namespace std;

// 存放多项式某项的结点结构
struct node
{
    int exp;           // 表示指数
    int coef;          // 表示系数
    struct node *next; // 指向下一个结点的指针
};

typedef struct node *PNODE;

/*
  函数功能：生成多项式
  函数名：createPoly
  函数参数：无
  返回值：指向多项式的头指针
*/
PNODE createPoly(void)
{
    //在此处填写代码，能实现创建一个多项式并返回多项式头指针的函数
	//注意：头指针不存放多项式的项。 
    /**********  Begin **********/
    PNODE head=new struct node;
    head->next=NULL;
    PNODE p=head;
    int n,a;
    cin>>n;
    cin>>a;
    while(n!=0&&a!=0){
      PNODE q=new struct node;
      q->coef=n;
      q->exp=a;
      q->next=NULL;
      p->next=q;
      p=p->next;
     cin>>n>>a;
   }
    p->coef=0;
    p->exp=0;
    return head;
    /**********  End  **********/
}

/*
   函数功能：进行多项式相加
   函数名：addPoly
   函数参数：polyAddLeft ：加法左边多项式头指针, polyAddRight：加法右边多项式头指针
   返回值：指向结果多项式的头指针
*/
PNODE addPoly(PNODE polyAddLeft, PNODE polyAddRight)
{
    // 在此处填写代码，能实现创两个多项式相加并返回结果多项式头指针的函数
    /**********  Begin **********/
    PNODE sum=new struct node;
    sum=NULL;
    PNODE p1=polyAddLeft->next;
    PNODE p2=polyAddRight->next;
    PNODE s=sum->next;
    while(p1->exp!=0&&p1->coef!=0&&p2->exp!=0&&p2->coef!=0){
        if(p1->exp<p2->exp){
            s->coef=p1->coef;
            s->exp=p1->exp;
            p1=p1->next;
            s=s->next;
        }
        if(p1->exp>p2->exp){
            s->coef=p2->coef;
            s->exp=p2->exp;
            p2=p2->next;
            s=s->next;
        }
        if(p1->exp==p2->exp){
            s->coef=p1->coef+p2->coef;
            s->exp=p1->exp;
            s=s->next;
            p1=p1->next;
            p2=p2->next;
        }
    }
    return sum;
    /**********  End **********/
}

/*
   函数功能：输出多项式
   函数名：printPoly
   函数参数：待输出多项式的头指针poly
   返回值：无
*/
void printPoly(PNODE poly)
{
    // 在此处填写代码，能实现按格式输出多项式的功能，输出格式样例见说明
    /**********  Begin **********/
    poly = poly->next;
    while(poly->exp!=0&&poly->coef!=0){
        if(poly->next->exp!=0&&poly->next->coef!=0)
        cout<<poly->coef<<"x^"<<poly->exp<<"+";
        else
        cout<<poly->coef<<"x^"<<poly->exp;
    }
    /**********  End **********/
}

#endif