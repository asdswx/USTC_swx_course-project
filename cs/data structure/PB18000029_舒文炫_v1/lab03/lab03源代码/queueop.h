typedef struct qwq{
    path* queuelist;
    int maxlen;
    int currlen;
}my_queue;

my_queue* initqueue(int maxlen);//初始化队列
//常规方法
my_queue* enqueue(my_queue *q,path p);//常规入队列
int dequeue(my_queue *q,path* p);//常规出队列
int printqueue(my_queue *q);//打印队列
//二叉堆
my_queue* enheapqueue(my_queue *q,path p);//入二叉堆
int deheapqueue(my_queue* q,path* p);//拿出二叉堆根节点

my_queue* initqueue(int maxlen){
    my_queue* q;
    q=(my_queue*)malloc(sizeof(my_queue));
    q->maxlen=maxlen;
    q->currlen=0;
    q->queuelist=(path*)malloc((maxlen+1)*sizeof(path));
    return q;
}

my_queue* enqueue(my_queue* q,path p){
    int j,k;
    if(q->currlen>=q->maxlen){
        printf("overflow!\n");
         exit(-1);
    }

    for(j=0;j<q->currlen;j++){
        if(q->queuelist[j].length>p.length)
            break;
    }
    if(j>=q->currlen){
        q->queuelist[j].vex=p.vex;
        q->queuelist[j].length=p.length;
    }
    else{
        for(k=q->currlen;k>j;k--){
            q->queuelist[k].vex=q->queuelist[k-1].vex;
            q->queuelist[k].length=q->queuelist[k-1].length;
        }
        q->queuelist[j].vex=p.vex;
        q->queuelist[j].length=p.length;
    }
    q->currlen++;
    return q;
}

int dequeue(my_queue* q,path* p){
    int k;
    if(q->currlen==0){
        return(-1);
    }
    p->length=q->queuelist[0].length;
    p->vex=q->queuelist[0].vex;
    for(k=0;k<q->currlen-1;k++){
        q->queuelist[k].length=q->queuelist[k+1].length;
        q->queuelist[k].vex=q->queuelist[k+1].vex;
    }
    q->currlen--;
    return 0;
}

int printqueue(my_queue *q){
    int i;
    for(i=0;i<q->currlen;i++){
        printf("%d,%d->",q->queuelist[i].vex,q->queuelist[i].length);

    }
    printf("\n");
}

my_queue* enheapqueue(my_queue *q,path p){
    int j,k;
    if(q->currlen>=q->maxlen){
        printf("overflow!\n");
         exit(-1);
    }
    for(j=q->currlen+1;j>1;j=j/2){
        if(q->queuelist[j/2].length>p.length){
            q->queuelist[j].length=q->queuelist[j/2].length;
            q->queuelist[j].vex=q->queuelist[j/2].vex;
        }
        else{

            break;
        }

    }
            q->queuelist[j].length=p.length;
            q->queuelist[j].vex=p.vex;
            q->currlen++;
            return q;

}

int deheapqueue(my_queue* q,path* p){
    int k;
    if(q->currlen==0){
        return(-1);
    }
    p->length=q->queuelist[1].length;
    p->vex=q->queuelist[1].vex;
    q->currlen--;
    for(k=2;k<=q->currlen;k=k*2){
        if(k<q->currlen&&(q->queuelist[k].length>q->queuelist[k+1].length))
            k++;
        if(k<=q->currlen&&(q->queuelist[q->currlen+1].length>q->queuelist[k].length)){
            q->queuelist[k/2].length=q->queuelist[k].length;
            q->queuelist[k/2].vex=q->queuelist[k].vex;
        }
        else
            break;

    }
    q->queuelist[k/2].length=q->queuelist[q->currlen+1].length;
    q->queuelist[k/2].vex=q->queuelist[q->currlen+1].vex;
    return 0;
}
