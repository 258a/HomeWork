#include<iostream>
#include<vector>
using namespace std;
//定义树节点
struct TreeNode{
    int value;
    struct TreeNode *l,*r;
};
typedef TreeNode *PTree;
PTree T=NULL;
//链表节点
struct ListNode{
    PTree info;
    struct ListNode *next=NULL;
};
typedef ListNode *PList;
//链表头节点
struct Head{
    int num=0;
    PList next=NULL;
};
typedef Head *PHead;
PHead L=new Head;
//创建一个链表节点
PList createList(PTree info,PList L){
    PList p=new ListNode;
    p->info=info;
    p->next=L;
    return p;
}
//头插法插入链表
void insertList(PHead L,PTree T){
    PList p=L->next;
    if(p==NULL||T->value<p->info->value){
        PList q=createList(T,p);
        L->next=q;
        L->num++;
        return;
    }
    while(p->next!=NULL){
        if(p->next->info->value>T->value&&p->info->value<T->value){
            PList q=createList(T,p->next);
            p->next=q;
            L->num++;
            return;
        }
        p=p->next;
    }
    PList q=createList(T,NULL);
    p->next=q;
    L->num++;
    return;
}
//返回移除的链表头节点
PList deleteHead(PHead L){
    PList p=L->next;
    L->next=p->next;
    L->num--;
    return p;
}
// 创建一个树节点
PTree createNode(int value,PTree l,PTree r){
    PTree newtree = new TreeNode;
    newtree->value = value;
    newtree->l=l;
    newtree->r=r;
    insertList(L,newtree);
    return newtree;
}
//初始化
void init(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        createNode(x,NULL,NULL);
    }
}
//构造树
void BuildTree(){
    while(L->num>1){
        PTree ltree=deleteHead(L)->info;
        PTree rtree=deleteHead(L)->info;
        T=createNode(ltree->value+rtree->value,ltree,rtree);
    }
}
//哈夫曼树编码
void Huffman(PTree T,vector<int> code){
    if(T->l==NULL&&T->r==NULL){
        cout<<T->value<<' ';
        for(vector<int>::iterator i=code.begin();i!=code.end();i++){
            cout<<*i;
        }
        cout<<endl;
        return;
    }
    code.push_back(0);
    Huffman(T->l,code);
    code.pop_back();
    code.push_back(1);
    Huffman(T->r,code);
    code.pop_back();
    return;
}

int main(){
    init();
    BuildTree();
    vector<int> code;
    Huffman(T,code);
    return 0;
}