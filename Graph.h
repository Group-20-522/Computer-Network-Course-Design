#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

#define maxValue 100000000.0 //��󸡵���
#define max 100

struct Edge//�߽�㶨��
{
    int dest;//��һ��·�ɴ���
    int metric;//����
    struct Edge *next;
    Edge():next(nullptr){};
    Edge(int dest):dest(dest),next(nullptr){}//���캯��
};


struct Vertex//·�ɽ��
{
    char route[8];//·�ɺ�
    char network[15];//���������
    struct Edge *head;//ָ��߽������ͷ
};

class Graphlnk
{
private:
    int maxVertexs;//����·������Ŀ
    int numVertexs;//��ǰ·������Ŀ
public:
    Vertex NodeTable[max];//�����

    Graphlnk(int sz=max);
    int getNodeDest(char *route);             //�õ�·������Ӧ����
    void getName(int i,char *route);          //ȡ���Ŵ����·����
    int NumberOfVertices(){return numVertexs;}//���ص�ǰ·������Ŀ
    int getName_Net(char *network);           //ȡ����Ź�����·�ɴ���
    int getMetric_Vehicle(int v1,int v2);//������������
    bool insertVertex(char *route,char *network);//������·����
    bool deleteVertex(char *route);//ɾ����·����
    bool insertEdge(int v1,int v2,int mertic);//�����±�
    bool deleteEdge(int v1,int v2);//ɾ����
    bool Cheat(char *route);//cheat�Ƿ��Ѵ��·����
    bool Cheat_Edge(char *route1,char *route2);//����Ƿ��д�·��
};

#endif // GRAPH_H_INCLUDED
