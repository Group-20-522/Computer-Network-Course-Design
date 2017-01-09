#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

#define maxValue 100000000.0 //最大浮点数
#define max 100

struct Edge//边结点定义
{
    int dest;//下一个路由代号
    int metric;//度量
    struct Edge *next;
    Edge():next(nullptr){};
    Edge(int dest):dest(dest),next(nullptr){}//构造函数
};


struct Vertex//路由结点
{
    char route[8];//路由号
    char network[15];//连接网络号
    struct Edge *head;//指向边结点链表头
};

class Graphlnk
{
private:
    int maxVertexs;//允许路由器数目
    int numVertexs;//当前路由器数目
public:
    Vertex NodeTable[max];//顶点表
    
    Graphlnk(int sz=max);
    int getNodeDest(char *route);             //得到路由器对应代号
    void getName(int i,char *route);          //取代号代表的路由器
    int NumberOfVertices(){return numVertexs;}//返回当前路由器数目
    int getName_Net(char *network);           //取网络号关联的路由代号
    int getMetric_Vehicle(int v1,int v2);//返回两点间度量
    bool insertVertex(char *route,char *network);//插入新路由器
    bool deleteVertex(char *route);//删除此路由器
    bool insertEdge(int v1,int v2,int mertic);//插入新边
    bool deleteEdge(int v1,int v2);//删除边
    bool Cheat(char *route);//cheat是否已存此路由器
    bool Cheat_Edge(char *route1,char *route2);//检查是否有此路径
};

#endif // GRAPH_H_INCLUDED
