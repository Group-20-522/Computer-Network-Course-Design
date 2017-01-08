#ifndef MANAGE_H_INCLUDED
#define MANAGE_H_INCLUDED

#include "Graph.h"
#include <fstream>
#include <string>

char filename1[50]="./Topology.txt";//������ļ�����
//char filename2[50]="./Routing_Table.txt";//·�ɱ�������ļ���
Graphlnk Cloud;

using namespace std;


void manage();
void FinData(Graphlnk &G,char *filename);   //·�ɱ����˵Ľ���
void Foutdata(char *route);    //���·�ɱ�
void Shortest_Path(Graphlnk &G,int v,int *dist,int *path);  //Dijkstra���·���㷨
void Out(Graphlnk G,int *path,int *dist,int v1,int v2,int &metric,char *route);//������·����һ�ڽ�·�ɱ�
void save(Graphlnk &G,char *filename);

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
        cout<<"\t��ȡ����ʧ��"<<endl;
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
        if(G.Cheat(route1)==true||G.Cheat(route2)==true)//û�д�·����
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

void Foutdata(Graphlnk G,char *route)    //���·�ɱ�
{
    int dist[max],path[max];
    int metric,v1;
    v1=G.getNodeDest(route);
    Shortest_Path(G,v1,dist,path);
    /*
    ofstream fout;
    remove(filename2);
    fout.open(filename2);
    if(!fout)
    {
        cout<<"����ʧ��"<<endl;
        exit(1);
    }*/
    int n=G.NumberOfVertices();
    cout<<"\tĿ������IP\t����\t��һ��·�ɱ�\n";
    for(int i=0;i<n;++i)
    {
            cout<<"\t "<<G.NodeTable[i].network<<"\t";
            Out(G,path,dist,v1,i,metric,route);
            cout<<metric<<"\t";
            if(route[0]=='0')
            {
                cout<<"ֱ�ӽ���"<<endl;
            }
            else
            {
                cout<<route<<endl;
            }
    }
    //fout.close();
}

void Shortest_Path(Graphlnk &G,int v,int *dist,int *path)
{
    int n=G.NumberOfVertices();//��·������Ŀ
    bool *S=new bool[n];
    int i,j,k,w,min,u;
    for(i=0;i<n;++i)//��ʼ��
    {
        dist[i]=G.getMetric_Vehicle(v,i);//
        S[i]=false;
        if(i!=v&&dist[i]<maxValue)
        {
            path[i]=v;//ֱ��·��
        }
        else
        {
            path[i]=-1;//����ֱ��
        }
    }
    S[v]=true;//����
    dist[v]=0;//����
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
        for(k=0;k<n;++k)//�Ƚϸ���
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

void Out(Graphlnk G,int *path,int *dist,int v1,int v2,int &metric,char *route)//������·����һ�ڽ�·�ɱ�
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
