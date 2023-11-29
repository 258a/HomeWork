#include<stdio.h>
#define  MAXNUM   20

typedef int DataType;
struct  SeqQueue {              /* 顺序队列类型定义 */
    int  f, r;
    DataType q[MAXNUM];
};

typedef struct SeqQueue* PSeqQueue;     /* 顺序队列类型的指针类型 */

PSeqQueue createEmptyQueue_seq(void) {
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu == NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return (paqu);
}

int isEmptyQueue_seq(PSeqQueue paqu) {
    return paqu->f == paqu->r;
}
/* 在队列中插入一元素x */
void  enQueue_seq(PSeqQueue paqu, DataType x) {
    if ((paqu->r + 1) % MAXNUM == paqu->f)
        printf("Full queue.\n");
    else {
        // 补充代码（1） begin-----------
        paqu->q[paqu->r]=x;
        paqu->r=(paqu->r+1)%MAXNUM;


        
        // 补充代码（1） end ------------        
    }
}

/* 删除队列头部元素 */
void  deQueue_seq(PSeqQueue paqu) {
    if (paqu->f == paqu->r)
        printf("Empty Queue.\n");
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* 对非空队列,求队列头部元素 */
DataType  frontQueue_seq(PSeqQueue paqu) {
    return (paqu->q[paqu->f]);
}

void farmerProblem() {
    int movers, i, location, newlocation;
    int t;
    int route[16];        /*记录已考虑的状态路径*/
    PSeqQueue moveTo;   /*定义队列moveTo */
    // -------- 补充代码（3） begin -----------------
    moveTo=createEmptyQueue_seq();
    enQueue_seq(moveTo,0x00);
    for(int i=0;i<16;i++){
        route[i]=-1;
    }
    route[0]=0;
    while(!isEmptyQueue_seq(moveTo)&&route[15]==-1){
        location=frontQueue_seq(moveTo);
        deQueue_seq(moveTo);
        for(int k=1;k<=8;k<<=1){
            if((0!=(location&&0x08))==(0!=(location&&k))){
                newlocation=location^(0x08|k);
            }
            if(safe(newlocation)&&route[newlocation]==-1){
                route[newlocation]=location;
                enQueue_seq(moveTo,newlocation);
            }
        }
    }
    // -------- 补充代码（3） end -----------------

    /* 打印出路径 */
    if (route[15] != -1) {
        printf("The reverse path is:\n");
        for (location = 15; location >= 0; location = route[location]) {
            printf("The location is : %d\n", location);
            if (location == 0) return;
        }
    }
    else
        printf("No solution.\n");
}