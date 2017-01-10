#ifndef MANAGE_H_INCLUDED
#define MANAGE_H_INCLUDED

#define max 100
#include "Graph.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
char filename1[50]="./Topology.txt";//读入的文件名字
Graphlnk Cloud;
using namespace std;


void manage();
void Tree();
void FinData(Graphlnk &G,char *filename);   //路由表拓扑的建立
void Foutdata(char *route);    //输出路由表
void Shortest_Path(Graphlnk &G,int v,int *dist,int *path);  //Dijkstra最短路径算法
void Out(Graphlnk G,int *path,int *dist,int v1,int v2,int &metric,char *route);//输出最短路径第一邻接路由表
void save(Graphlnk &G,char *filename);
void Out_path(Graphlnk G,int *path,int *dist,int v);
void Trees_(Graphlnk G,char *path,int v1,int m);


void manage()
{
    FinData(Cloud,filename1);
}


void FinData(Graphlnk &G,char *filename)
{
    fstream fin;
    fin.open(filename);
    if(!fin)
    {
        cout<<"\t读取数据失败"<<endl;
        exit(1);
    }
    char line[1024];
    int num;
    if(fin.peek()=='r')
    {
        fin.getline(line,1024);
        fin>>line;
        fin>>num;
    }
    for(int i=0;i<num;++i)
    {
        char route[5];
        char network[10];
        fin>>route;
        fin>>network;
        if(G.Cheat(route)==true)
        {
            G.insertVertex(route,network);
        }
    }
    fin.getline(line,1024);
    fin.getline(line,1024);
    while(fin.peek()!=EOF)
    {
        char route1[5],route2[5];
        int metric;
        fin>>route1;
        fin>>route2;
        if(G.Cheat(route1)==true||G.Cheat(route2)==true)//没有此路由器
        {
            fin>>metric;
        }
        else
        {
            fin>>metric;
            int m,n;
            m=G.getNodeDest(route1);
            n=G.getNodeDest(route2);
            G.insertEdge(m,n,metric);
        }
    }
    fin.close();
}


void Trees_(Graphlnk G,int *path,int v1,int m)
{
    char route[10];
    int n=G.NumberOfVertices();
    for(int i=0;i<n;++i)
    {
        if(path[i]==v1)
        {
            for(int k=0;k<m;++k)
            {
                cout<<"    ";
            }
            cout<<"--";
            G.getName(i,route);
            cout<<route<<endl;
            Trees_(G,path,i,m+1);
        }
    }
    return;
}


void Foutdata(Graphlnk G,char *route)    //输出路由表
{
    int dist[100],path[100];
    int metric,v1,first;
    first=G.getNodeDest(route);
    v1=first;
    Shortest_Path(G,v1,dist,path);
    int n=G.NumberOfVertices();
    cout<<"\t目的网络IP\t距离\t下一跳路由表\n";
    for(int i=0;i<n;++i)
    {
        cout<<"\t "<<G.NodeTable[i].network<<"\t";
        Out(G,path,dist,v1,i,metric,route);
        cout<<metric<<"\t";
        if(route[0]=='0')
        {
            cout<<"直接交付"<<endl;
        }
        else
        {
            cout<<route<<endl;
        }
    }
    cout<<endl;
    G.getName(first,route);
    cout<<"  "<<route<<endl;
    Trees_(G,path,v1,1);
}



void Shortest_Path(Graphlnk &G,int v,int *dist,int *path)
{
    int n=G.NumberOfVertices();//得路由器数目
    bool *S=new bool[n];
    int i,j,k,w,min,u;
    for(i=0;i<n;++i)//初始化
    {
        dist[i]=G.getMetric_Vehicle(v,i);//
        S[i]=false;
        if(i!=v&&dist[i]<maxValue)
        {
            path[i]=v;//直达路径
        }
        else
        {
            path[i]=-1;//不能直达
        }
    }
    S[v]=true;//本身
    dist[v]=0;//本身
    for(i=0;i<n-1;++i)
    {
        min=maxValue;
        u=v;
        for(j=0;j<n;++j)
        {
            if(S[j]==false&&dist[j]<min)
            {
                u=j;
                min=dist[j];
            }
        }
        S[u]=true;
        for(k=0;k<n;++k)//比较更新
        {
            w=G.getMetric_Vehicle(u,k);
            if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k])
            {
                dist[k]=dist[u]+w;
                path[k]=u;
            }
        }
    }
}
void Out(Graphlnk G,int *path,int *dist,int v1,int v2,int &metric,char *route)//输出最短路径第一邻接路由表
{
    metric=dist[v2];
    if(v1==v2)
    {
        route[0]='0';
    }
    else
    {
        int temp=v2;
        while(path[temp]!=v1)
        {
            temp=path[temp];
        }
        G.getName(temp,route);
    }
}
void save(Graphlnk &G,char *filename)
{
    ofstream fout;
    int numofVets=G.NumberOfVertices();
    fout.open(filename);
    fout<<"route    and    network"<<endl;
    fout<<"number: "<<numofVets<<endl;
    for(int i=0;i<numofVets;i++)
    {
        fout<<G.NodeTable[i].route<<"\t\t"<<G.NodeTable[i].network<<endl;
    }
    fout<<"route1   to   route2   is   metric"<<endl;
    Edge *p;
    for(int i=0;i<numofVets;i++)
    {
        p=G.NodeTable[i].head;
        while(p!=nullptr)
        {
            if(i<p->dest)
            {
                fout<<G.NodeTable[i].route<<"\t\t";
                fout<<G.NodeTable[p->dest].route<<"\t\t";
                fout<<p->metric<<endl;
            }
            p=p->next;
        }
    }
    fout.close();
}
#endif // MANAGE_H_INCLUDED
