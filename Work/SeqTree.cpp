 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 /* 
 定义顺序存储结构
  */
  struct seqTree
  {
    char info[100];
    int size;
  };

/*辅助功能：逐个输出顺序表的元素，元素之间以空格为界*/
void printTree(struct seqTree *T)
{
  for(int i=0;i<T->size;i++){
    printf("%c ",T->info[i]);
  }
}

/*第一关*/
struct seqTree *createSeqTree()
{
  //此处编写代码实现二叉树的初始化，包括输入数据
  struct seqTree *T = (struct seqTree *)malloc(sizeof(struct seqTree));
    T->size = 0;
    gets(T->info);
    T->size = strlen(T->info);
    return T;
}

/*第二关，返回二叉树的根结点的值，若二叉树为空，则返回#*/
char root(struct seqTree *T)
{
  if(T->size==0)
  return '#';
  else
  return T->info[0];
}

/*第二关，求二叉树T中指定结点ch的双亲结点，返回值是双亲结点的下标，若双亲不存在，则返回-1*/
int parent(struct seqTree *T ,char ch)
{
  for(int i=0;i<T->size;i++){
    if(T->info[i]==ch){
      if(i==0){
        return -1;
      }
      if(i>=0&&i<=T->size&&T->info[i]!=' '){
        return (i-1)/2;
      }
    }
  }
  return -1;
}

/*第二关，求二叉树T中指定结点ch的左孩子的下标，若左孩子不存在，则返回-1*/
int leftChild(struct seqTree *T ,char ch)
{
  for(int i=0;i<T->size;i++){
    if(T->info[i]==ch){
      if(i>=0&&(i*2+1)<=T->size&&T->info[i*2+1]!=' '){
        return 2*i+1;
      }
    }
  }
  return -1;
}

/*第二关，求二叉树T中指定结点ch的右孩子的下标，若左孩子不存在，则返回-1*/
int rightChild(struct seqTree *T ,char ch)
{
  for(int i=0;i<T->size;i++){
    if(T->info[i]==ch){
      if(i>=0&&(i*2+2)<=T->size&&T->info[i*2+2]!=' '){
        return 2*i+2;
      }
    }
  }
  return -1;
}

/*第三关：层序遍历二叉树，输出遍历得到的结点，结点之间不需要空格*/
void levelOrder(struct seqTree *T )
{
  for(int i=0;i<T->size;i++){
    if(T->info[i]!=' ')
    printf("%c",T->info[i]);
  }
}

/*第四关：先序遍历二叉树，输出遍历得到的结点，结点之间不需要空格*/
void preOrder(struct seqTree *T ,int root)
{
if(T->info[root]==' ')return;
printf("%c",T->info[root]);
if(2*root+1<=T->size)preOrder(T,2*root+1);
if(2*root+2<=T->size)preOrder(T,2*root+2);
}



int main(void)
{
  struct seqTree *T = createSeqTree();
  /*printTree(T);*/ //测评第一关时，把本行代码放开
  /*printf("%c\n",root(T)); //  测评第二关时，把该代码块放开
    printf("%d\n",leftChild(T,'A'));
    printf("%d\n",rightChild(T,'A'));
    printf("%d\n",parent(T,'A'));
     */
   /*levelOrder(T);*/ //测评第三关时，把本行代码放开 
   /*preOrder(T,0);*/ //测评第四关时，把本行代码放开 

}

