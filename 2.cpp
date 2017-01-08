#include <iostream>
#include<string.h>
#include <vector>
#include <fstream>
#define maxValue 100000000.0 //最大浮点数
#define max 100
using namespace std;
char filename1[50]="/Users/apple/Desktop/Topology";
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
    int route;//路由号
    char network[10];//连接网络号
    struct Edge *head;//指向边结点链表头
};

/*struct Routing_Table//路由表
 {
 int network;//网络号
 int metric;//度量
 int route;//路由号
 };*/

class Graphlnk
{
private:
    int maxVertexs;//允许路由器数目
    int numVertexs;//当前路由器数目
    Vertex NodeTable[max];//顶点表
    
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
    int getNodeDest(int route)//得到路由器对应代号
    {
        for(int i=0;i<numVertexs;++i)
        {
            if(NodeTable[i].route==route)
            {
                return i;
            }
        }
        return -1;
    }
    int getName(int i)//取代号代表的路由器
    {
        return NodeTable[i].route;
    }
    int NumberOfVertices()//返回当前路由器数目
    {
        return numVertexs;
    }
    int getName_Net(char *network)//取网络号关联的路由器
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
    bool insertVertex(int route,char *network);//插入新路由器
    bool deleteVertex(int route);//删除此路由器
    bool insertEdge(int v1,int v2,int mertic);//插入新边
    bool deleteEdge(int v1,int v2);//删除边
    bool Cheat(int route);//cheat是否已存此路由器
    //bool Cheat(char *network);//检查是否有此网
    void Foutdata(int route);
};

bool Graphlnk::Cheat(int route)
{
    for(int i=0;i<numVertexs;++i)
    {
        if(NodeTable[i].route==route)
        {
            return false;//已有，不需要新加入
        }
    }
    return true;//需要加入此路由器
}

/*bool Graphlnk::Cheat(char *network)
 {
 for(int i=0;i<numVertexs;++i)
 {
 if(strcmp(NodeTable[i].network,network)==0)
 {
 return true;//存在此网
 }
 }
 return false;
 }*/

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




bool Graphlnk::insertVertex(int route,char *network)//添加路由器
{
    if(numVertexs==maxVertexs)
    {
        cerr<<"满，不能插入"<<endl;
        return false;
    }
    NodeTable[numVertexs].route=route;
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


bool Graphlnk::deleteVertex(int route)//删除路由器
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
                delete s;
            }
        }
        NodeTable[v].head=p->next;
        delete p;
    }
    numVertexs--;
    NodeTable[v].route=NodeTable[numVertexs].route;//填补
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
        //cout<<"p->dest="<<v2<<endl;
        p->metric=metric;
        //cout<<"p->metric="<<metric<<endl;
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
        //cout<<"q->dest="<<v1<<endl;
        q->metric=metric;
        //cout<<"q->metric="<<metric<<endl<<endl;
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
        //cout<<"直达到"<<i+1<<"花费"<<dist[i]<<endl;//****
        S[i]=false;
        if(i!=v&&dist[i]<maxValue)
        {
            path[i]=v;//直达路径
            //cout<<i<<"的前面是"<<v<<endl;//***
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
                //cout<<"此时的u"<<u+1<<"  此时的w"<<w<<endl;
                //cout<<"更新到"<<k+1<<"花费"<<dist[k]<<endl;//****
                path[k]=u;
                //cout<<"更新   "<<i+1<<"的前面是"<<v+1<<endl;//***
            }
        }
    }
}





void Out(Graphlnk G,int *path,int *dist,int v1,int v2,int &metric,int &route)//输出最短路径第一邻接路由表
{
    metric=dist[v2];
    if(v1==v2)
    {
        route=0;
    }
    else
    {
        int temp=v2;
        while(path[temp]!=v1)
        {
            temp=path[temp];
        }
        route=G.getName(temp);
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
        int route;
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
        int route1,route2;
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

void Graphlnk::Foutdata(int route)
{
    int dist[max],path[max];
    int metric,v1;
    v1=getNodeDest(route);
    Shortest_Path(*this,v1,dist,path);
    //remove("/Users/apple/Desktop/bbc");
    //fout.open("/Users/apple/Desktop/bbc");
    /*if(!fout)
     {
     cout<<"保存失败"<<endl;
     exit(1);
     }*/
    int n=NumberOfVertices();
    cout<<"目的网络\t\t距离\t\t下一跳路由表\n";
    for(int i=0;i<n;++i)
    {
        cout<<NodeTable[i].network<<"\t\t";
        Out(*this,path,dist,v1,i,metric,route);
        cout<<metric<<"\t\t";
        if(route==0)
        {
            cout<<"直接交付"<<endl;
        }
        else
        {
            cout<<route<<endl;
        }
        
    }
    
    //fout.close();
}


int main()
{
    Graphlnk Cloud(max);
    FinData(Cloud,filename1);
    int route;
    /*cout<<"路由号？？:";
     cin>>route;
     Cloud.Foutdata(route);*/
    char a='@';
    while(a!='#')
    {
        cout<<"---------------------------"<<endl;
        cout<<"-  生成指定路由器的路由表->1  -"<<endl;
        cout<<"-     修改网络的拓扑-->2     -"<<endl;
        cout<<"-          退出-->#        -"<<endl;
        cout<<"---------------------------"<<endl;
        cin>>a;
        switch(a)
        {
            case '1':
                cout<<"路由号？？:";
                cin>>route;
                if(Cloud.Cheat(route)==true)
                {
                    cout<<"没有此路由器"<<endl;
                }
                else
                {
                    Cloud.Foutdata(route);
                }
                break;
            case '2':
                cout<<"------------------------"<<endl;
                cout<<"-     去掉指定路由器->1  -"<<endl;
                cout<<"-     去掉指定边-->2     -"<<endl;
                cout<<"-        输入其他退出       -"<<endl;
                cout<<"------------------------"<<endl;
                char choose;
                cout<<"选择：";
                cin>>choose;
                if(choose=='1')
                {
                    cout<<"路由号？？:";
                    cin>>route;
                    Cloud.deleteVertex(route);
                }
                if(choose=='2')
                {
                    int route1,route2;
                    cout<<"相邻两路由器：：：";
                    cout<<"一端:";
                    cin>>route1;
                    cout<<"另一端:";
                    cin>>route2;
                    
                    Cloud.deleteEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2));
                }
                break;
            case '#':
                break;
            default:
                cout<<"选项错误"<<endl;
                break;
        }
        
        
        
        
        
    }
    
    
}