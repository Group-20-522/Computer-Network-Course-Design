#include <list>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <queue>
using namespace std;
#define MAX_VERTEX_NUM 600
#define INFINITY 1000000//将INFINITY定义为无穷大的值
//保存每个顶点信息的数据结构
struct GraphNode{
    bool known;//当前顶点距离起点的距离是否确定
    int dist;//当前顶点到起点的最短距离
    int path;//当前顶点距离起点的最短路径的前一个顶点
};
typedef struct Node{
    int edge_num;//边号
    int src;//源点
    int vertex;//自身
    int weight;//边的权重
}Node;
class Graph{
private:
    int edge_num;//图边的个数
    int vertex_num;//图的顶点数目
    list<Node> * graph_list;//邻接表
    vector<GraphNode> nodeArr;//保存每个顶点信息的数组
public:
    Graph(){}
    Graph(char* graph[], int edgenum);
    ~Graph();
    void print();
    void dijkstra(int src);
    void printShorestPath();
private:
    vector<int> get_graph_value(char* graph[], int columns);
    void addEdge(char* graph[], int columns);
};
void Graph::dijkstra(int src)
{
    //初始化顶点信息
    for(int i = 0; i < vertex_num; ++i){
        nodeArr[i].known = false;
        nodeArr[i].dist = INFINITY;
        nodeArr[i].path = 0;
    }
    //重要的一步，开启算法的关键一步
    nodeArr[src].dist = 0;
    for(; ;){
        //找到unknown的dist最小的顶点
        int v = 0;
        int max = INFINITY;
        for(int i = 0; i < vertex_num; ++i){
            if(!nodeArr[i].known && (max > nodeArr[i].dist)){
                max = nodeArr[i].dist;
                v = i;
            }
        }
        //没有找到满足条件的顶点,退出算法
        if(max == INFINITY)
            break;
        nodeArr[v].known = true;
        //更新与v相邻所有顶点w的dist,path
        for(list<Node>::iterator it = graph_list[v].begin(); it != graph_list[v].end(); ++it){
            if(!nodeArr[(*it).vertex].known){
                if(nodeArr[v].dist + (*it).weight < nodeArr[(*it).vertex].dist){
                    nodeArr[(*it).vertex].dist = nodeArr[v].dist + (*it).weight;
                    nodeArr[(*it).vertex].path = v;
                }
            }
        }
        
    }
}
void Graph::printShorestPath()
{
    cout << "顶点\t" << "known\t" << "dist\t" << "path" << endl;
    for(int i = 0; i < vertex_num; ++i){
        if(nodeArr[i].known)
            cout << i << "\t" << nodeArr[i].known << "\t" << nodeArr[i].dist << "\t" << nodeArr[i].path << endl;
    }
}
void Graph::print()
{
    cout << "******************************************************************" << endl;
    for(int i = 0 ; i < vertex_num; ++i){
        if(graph_list[i].begin() != graph_list[i].end()){
            cout << i << "-->";
            for(list<Node>::iterator it = graph_list[i].begin(); it != graph_list[i].end(); ++it){
                cout << (*it).vertex << "(边号:" << (*it).edge_num << ",权重:" << (*it).weight << ")-->";
            }
            cout << "NULL" << endl;
        }
    }
    cout << "******************************************************************" << endl;
}
vector<int> Graph::get_graph_value(char* graph[], int columns)
{
    vector<int> v;
    char buff[20];
    int i = 0, j = 0, val;
    memset(buff, 0, 20);
    while((graph[columns][i] != '\n') && (graph[columns][i] != '\0')){
        if(graph[columns][i] != ','){
            buff[j] = graph[columns][i];
            j++;
        }
        else{
            j = 0;
            val = atoi(buff);
            v.push_back(val);
            memset(buff, 0, 20);
        }
        i++;
    }
    val = atoi(buff);
    v.push_back(val);
    return v;
}
void Graph::addEdge(char* graph[], int columns)
{
    Node node;
    vector<int> v = get_graph_value(graph, columns);
    node.edge_num = v[0];
    node.src = v[1];
    node.vertex = v[2];
    node.weight = v[3];
    if(node.vertex > vertex_num)
        vertex_num = node.vertex;
    for(list<Node>::iterator it = graph_list[node.src].begin(); it != graph_list[node.src].end(); ++it){
        if((*it).vertex == node.vertex){
            if((*it).weight > node.weight){
                (*it).weight = node.weight;
            }
            return;
        }
    }
    graph_list[node.src].push_back(node);
}
Graph::Graph(char* graph[], int edgenum):nodeArr(MAX_VERTEX_NUM)
{
    edge_num =  edgenum;
    vertex_num = 0;
    graph_list = new list<Node>[MAX_VERTEX_NUM+1];
    for(int i = 0; i < edgenum; ++i){
        addEdge(graph, i);
    }
    //对顶点信息进行初始化
    for(int i = 0; i < MAX_VERTEX_NUM; ++i){
        nodeArr[i].known = false;
        nodeArr[i].dist = INFINITY;
        nodeArr[i].path = -1;//如果为-1，表示没有该点,配合dijkstra算法使用
    }
    vertex_num++;
}
Graph::~Graph()
{
    delete[] graph_list;
}