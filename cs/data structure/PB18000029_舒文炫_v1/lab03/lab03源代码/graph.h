#ifndef GRAPH
#define GRAPH
typedef struct ArcNode {  //结点的组成域
	int adjvex;   //边指向的顶点位置
	struct ArcNode* nextarc;   //指向下一条弧的指针
	int info;  //该弧相关信息指针（长度）
}ArcNode;
typedef struct VNode {   //表头结点
	ArcNode* firstarc;  //指向第一条依附该顶点的边的指针
}VNode, * AdjList;
typedef struct {   //图
	AdjList vertices;  //可以间接使用数组
	int vexnum, arcnum;    //图的当前顶点数和弧数
}ALGraph;
typedef struct {
	int vex;
	int length;
}path;








#endif // GRAPH
