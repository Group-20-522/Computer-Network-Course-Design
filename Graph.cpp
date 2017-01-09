#include "Graph.h"

Graphlnk::Graphlnk(int sz)
{
    maxVertexs=sz;
    numVertexs=0;
    for(int i=0;i<maxVertexs;++i)
    {
        NodeTable[i].head=nullptr;
    }
}

int Graphlnk::getNodeDest(char *route)//得到路由器对应代号
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

void Graphlnk::getName(int i,char *route)//取代号代表的路由器
{
    for(int m=0;m<5;++m)
    {
        route[m]=NodeTable[i].route[m];
    }
}

int Graphlnk::getName_Net(char *network) //取网络号关联的路由代号
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
        cerr<<"\t某一路由器不存在"<<endl;
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
    if(numVertexs==maxVertexs)
    {
        cerr<<"\t满，不能插入"<<endl;
        return false;
    }
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
            cerr<<"\t已存在此路线"<<endl;
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
            cerr<<"\t已存在此路线"<<endl;
            cout<<"\tv2:"<<v2+1<<"-v1:"<<v1+1<<endl;
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




