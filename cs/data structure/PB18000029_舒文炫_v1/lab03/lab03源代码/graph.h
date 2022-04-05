#ifndef GRAPH
#define GRAPH
typedef struct ArcNode {  //���������
	int adjvex;   //��ָ��Ķ���λ��
	struct ArcNode* nextarc;   //ָ����һ������ָ��
	int info;  //�û������Ϣָ�루���ȣ�
}ArcNode;
typedef struct VNode {   //��ͷ���
	ArcNode* firstarc;  //ָ���һ�������ö���ıߵ�ָ��
}VNode, * AdjList;
typedef struct {   //ͼ
	AdjList vertices;  //���Լ��ʹ������
	int vexnum, arcnum;    //ͼ�ĵ�ǰ�������ͻ���
}ALGraph;
typedef struct {
	int vex;
	int length;
}path;








#endif // GRAPH
