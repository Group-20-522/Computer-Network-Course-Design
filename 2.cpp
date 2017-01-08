#include <iostream>
#include<string.h>
#include <vector>
#include <fstream>
#include "stdlib.h"
#define maxValue 100000000.0 //最大浮点数
#define max 100
using namespace std;
<<<<<<< HEAD
char filename1[50]="./Topology.txt";//读入的文件名字
char filename2[50]="./Routing_Table.txt";//输出的文件名。暂时没用到
=======
char filename1[50]="/Users/tanlizhan/Desktop/Topology.txt";//读入的文件名字
char filename2[50]="/Users/tanlizhan/Desktop/Routing_Table.txt";//输出的文件名。暂时没用到
>>>>>>> origin/master
fstream fin;
ofstream fout;
struct Edge//边结点定义
{
    int dest;//下一个路由代号
    int metric;//度量
    struct Edge *next;
    Edge():next(NULL){};
    Edge(int dest):dest(dest),next(NULL){}//构造函数
};
struct Vertex//路由结点
{
    char route[5];//路由号
    char network[10];//连接网络号
    struct Edge *head;//指向边结点链表头
};
class Graphlnk
{
private:
    int maxVertexs;//允许路由器数目
    int numVertexs;//当前路由器数目
    Vertex NodeTable[max];//顶点表
<<<<<<< HEAD

=======
>>>>>>> origin/master
public:
    Graphlnk(int sz)
    {
        maxVertexs=sz;
        numVertexs=0;
        for(int i=0;i<maxVertexs;++i)
        {
            NodeTable[i].head=NULL;
        }
    }
    int getNodeDest(char *route)//得到路由器对应代号
    {
        for(int i=0;i<numVertexs;++i)
        {
            if(strcmp(NodeTable[i].route,route)==0)
            {
                return i;
            }
        }
        return -1;
    }
    void getName(int i,char *route)//取代号代表的路由器
    {
        for(int m=0;m<5;++m)
        {
            route[m]=NodeTable[i].route[m];
        }
    }
    int NumberOfVertices()//返回当前路由器数目
    {
        return numVertexs;
    }
    int getName_Net(char *network)//取网络号关联的路由代号
    {
        for(int i=0;i<numVertexs;++i)
        {
            if(strcmp(NodeTable[i].network,network)==0)
            {
                return i;
            }
        }
        return -1;
    }
    int getMetric_Vehicle(int v1,int v2);//返回两点间度量
    bool insertVertex(char *route,char *network);//插入新路由器
    bool deleteVertex(char *route);//删除此路由器
    bool insertEdge(int v1,int v2,int mertic);//插入新边
    bool deleteEdge(int v1,int v2);//删除边
    bool Cheat(char *route);//cheat是否已存此路由器
    bool Cheat_Edge(char *route1,char *route2);//检查是否有此路径
    void Foutdata(char *route);
};

bool Graphlnk::Cheat(char *route)
{
    for(int i=0;i<numVertexs;++i)
    {
        if(strcmp(NodeTable[i].route,route)==0)
        {
            return false;//已有，不需要新加入
        }
    }
    return true;//需要加入此路由器
}
bool Graphlnk::Cheat_Edge(char *route1,char *route2)
{
    int v1,v2;
    v1=getNodeDest(route1);
    v2=getNodeDest(route2);
    if(v1==-1||v2==-1)
    {
        cerr<<"某一路由器不存在"<<endl;
        return false;
    }
    else
    {
        Edge *p,*q;
        int mark=0;
        p=NodeTable[v1].head;
        q=NodeTable[v2].head;
        while(p!=NULL)
        {
            if(p->dest==v2)
            {
                mark=1;
                break;
            }
            p=p->next;
        }
        while(q!=NULL)
        {
            if(q->dest==v1&&mark==1)
            {
                return true;
            }
            q=q->next;
        }
    }
    return false;
}
int Graphlnk::getMetric_Vehicle(int v1,int v2)
{
    if(v1!=-1&&v2!=-1)
    {
        Edge *p=NodeTable[v1].head;
        while(p!=NULL)
        {
            if(p->dest==v2)
            {
                return p->metric;
            }
            p=p->next;
        }
    }
    return maxValue;
}
bool Graphlnk::insertVertex(char *route,char *network)//添加路由器
{
    /*if(numVertexs==maxVertexs)
     {
     cerr<<"满，不能插入"<<endl;
     return false;
     }*/
    for(int i=0;i<5;++i)
    {
        NodeTable[numVertexs].route[i]=route[i];
    }
    for(int i=0;i<10;++i)
    {
        NodeTable[numVertexs].network[i]=network[i];
    }
    numVertexs++;
    return true;
}
bool Graphlnk::deleteEdge(int v1,int v2)//删边
{
    if(v1!=-1&&v2!=-1)
    {
        Edge *p=NodeTable[v1].head;
        Edge *q=NULL;
        Edge *s=p;
        while(p!=NULL&&p->dest!=v2)
        {
            q=p;
            p=p->next;
        }
        if(p!=NULL)
        {
            if(p==s)
            {
                NodeTable[v1].head=p->next;
            }
            else
            {
                q->next=p->next;
            }
            delete p;
        }
        else
        {
            return false;
        }
        p=NodeTable[v2].head;
        q=NULL;
        s=p;
        while(p->dest!=v1)
        {
            q=p;
            p=p->next;
        }
        if(p==s)
        {
            NodeTable[v2].head=p->next;
        }
        else
        {
            q->next=p->next;
        }
        delete p;
        return true;
    }
    return false;
}
bool Graphlnk::deleteVertex(char *route)//删除路由器
{
    int v=getNodeDest(route);//得到路由器代号
    if(numVertexs==1||v<0||v>maxVertexs)
    {
        return false;
    }
    Edge *p,*s,*t;
    int k;
    while(NodeTable[v].head!=NULL)
    {
        p=NodeTable[v].head;//找到删除的顶点的边链表
        k=p->dest;
        s=NodeTable[k].head;//开始删除邻接顶点的边链表上的v点
        t=NULL;
        while(s!=NULL&&s->dest!=v)
        {
            t=s;
            s=s->next;
        }
        if(s!=NULL)
        {
            if(t==NULL)
            {
                NodeTable[k].head=s->next;
            }
            else
            {
                t->next=s->next;
            }
            delete s;
        }
        NodeTable[v].head=p->next;
        delete p;
    }
    numVertexs--;
    for(int i=0;i<5;++i)
    {
        NodeTable[v].route[i]=NodeTable[numVertexs].route[i];//填补
    }
    for(int i=0;i<10;++i)
    {
        NodeTable[v].network[i]=NodeTable[numVertexs].network[i];//填补
    }
    NodeTable[v].head=NodeTable[numVertexs].head;
    p=NodeTable[v].head;
    while(p!=NULL)
    {
        s=NodeTable[p->dest].head;
        while(s!=NULL)
        {
            if(s->dest==numVertexs)
            {
                s->dest=v;
                break;
            }
            else
            {
                s=s->next;
            }
        }
        p=p->next;
    }
    return true;
}
bool Graphlnk::insertEdge(int v1,int v2,int metric)//添边
{
    if(v1>=0&&v1<numVertexs&&v2>=0&&v2<numVertexs)
    {
        Edge *p=NodeTable[v1].head;
        Edge *q=NodeTable[v2].head;
        while(p!=NULL&&p->dest!=v2)
        {
            p=p->next;
        }
        if(p!=NULL)
        {
            cerr<<"已存在此路线"<<endl;
            return false;
        }
        p=new Edge;

        p->dest=v2;
        p->metric=metric;
        p->next=NodeTable[v1].head;
        NodeTable[v1].head=p;
        while(q!=NULL&&q->dest!=v1)
        {
            q=q->next;
        }
        if(q!=NULL)
        {
            cerr<<"已存在此路线"<<endl;
            cout<<"v2:"<<v2+1<<"-v1:"<<v1+1<<endl;
            return false;
        }
        q=new Edge;
        q->dest=v1;
        q->metric=metric;
        q->next=NodeTable[v2].head;
        NodeTable[v2].head=q;
        return true;
    }
    return false;
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
void FinData(Graphlnk &G,char *filename)
{
    fin.open(filename);
    if(!fin)
    {
        cout<<"读取数据失败"<<endl;
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

void Graphlnk::Foutdata(char *route)
{
    int dist[max],path[max];
    int metric,v1;
    v1=getNodeDest(route);
    Shortest_Path(*this,v1,dist,path);
    int n=NumberOfVertices();
    cout<<"       所查路由器路由表"<<endl;
    cout<<"目的网络\t\t距离\t\t下一跳路由表\n";
    for(int i=0;i<n;++i)
    {
<<<<<<< HEAD
            cout<<NodeTable[i].network<<"\t\t";
            Out(*this,path,dist,v1,i,metric,route);
            cout<<metric<<"\t\t";
            if(route[0]=='0')
            {
                cout<<"直接交付"<<endl;
            }
            else
            {
                cout<<route<<endl;
            }

    }

    //fout.close();
=======
        cout<<NodeTable[i].network<<"\t\t";
        Out(*this,path,dist,v1,i,metric,route);
        cout<<metric<<"\t\t";
        if(route[0]=='0')
        {
            cout<<"直接交付"<<endl;
        }
        else
        {
            cout<<route<<endl;
        }
    }
>>>>>>> origin/master
}
int main()
{
    Graphlnk Cloud(max);
    FinData(Cloud,filename1);
    char route[5];
    char a='@';
    while(a!='#')
    {
        cout<<"***********菜单***********"<<endl;
        cout<<"* 1.生成指定路由器的路由表  *"<<endl;
        cout<<"* 2.   修改当前网络拓扑    *"<<endl;
        cout<<"* 3.       退出          *"<<endl;
        cout<<"*************************"<<endl;
        cout<<"请输入对应执行步骤序号：";
        cin>>a;
        cout<<endl;
        switch(a)
        {
            case '1':
                cout<<"请输入路由号(输入格式为R?):";
                cin>>route;
                if(Cloud.Cheat(route)==true)
                {
                    cout<<"没有此路由器"<<endl;
                }
                else
                {
                    Cloud.Foutdata(route);
                    cout<<endl;
                }
                break;
            case '2':
                char route1[5],route2[5];
                cout<<"******子菜单*******"<<endl;
                cout<<"* 1.删除指定路由器 *"<<endl;
                cout<<"* 2. 删除指定边   *"<<endl;
                cout<<"* 3.添加指定路由器 *"<<endl;
                cout<<"* 4. 添加加指定边  *"<<endl;
                cout<<"*   输入其他退出   *"<<endl;
                cout<<"******************"<<endl;
                char choose;
                cout<<"请输入对应执行步骤序号：";
                cin>>choose;
                cout<<endl;
                if(choose=='1')
                {
                    cout<<"请输入路由号(输入格式为R?):";
                    cin>>route;
                    if(Cloud.Cheat(route)==true)
                    {
                        cout<<"图中没有该路由器"<<endl;
                    }
                    else
                    {
                        Cloud.deleteVertex(route);
                    }
                    cout<<endl;
                }
                if(choose=='2')
                {
                    cout<<"请分别输入该边两端路由器"<<endl;
                    cout<<"一端:";
                    cin>>route1;
                    cout<<"另一端:";
                    cin>>route2;
                    if(Cloud.Cheat_Edge(route1,route2)==true)//存在边
                    {
                        Cloud.deleteEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2));
                    }
                    else
                    {
                        cout<<"不存在此边"<<endl;
                    }
                    cout<<endl;
                }
                if(choose=='3')
                {
                    cout<<"请输入路由号(输入格式为R?):";
                    cin>>route;
                    if(Cloud.Cheat(route)==false)
                    {
                        cout<<"图中已有该路由器"<<endl;
                    }
                    else
                    {
                        char network[10];
                        cout<<"请输入该路由器连接的网络(输入格式为?.x.x.x):";
                        cin>>network;
                        Cloud.insertVertex(route, network);
                    }
                    cout<<endl;
                }
                if(choose=='4')
                {
                    cout<<"请分别输入该边两端路由器"<<endl;
                    cout<<"一端:";
                    cin>>route1;
                    cout<<"另一端:";
                    cin>>route2;
                    if(Cloud.Cheat_Edge(route1,route2)==true)
                    {
                        cout<<"此边已存在"<<endl;
                    }
                    else
                    {
                        int mertic;
                        cout<<"该边的度量为:";
                        cin>>mertic;
                        Cloud.insertEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2),mertic);
                    }
                    cout<<endl;
                }
                break;
            case '3':
                return 0;
            default:
                cout<<"选项错误"<<endl;
                break;
        }
<<<<<<< HEAD





    }


=======
    }
    return 0;
>>>>>>> origin/master
}


