#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include "Manage.h"

using namespace std;

char Menu();
void menu();
void menu1();
void menu2();
//void quit();

int main()
{   manage();   //生成路由拓扑图
    menu();
    return 0;
}

char Menu() //菜单格式
{
    system("cls");
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-       1.  生成指定路由器的路由表      -"<<endl;
    cout<<"\t-       2.  修改网络的拓扑              -"<<endl;
    cout<<"\t-       0.  保存并退出                  -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t:-> _";
    char x;
    do{cout<<"\b";cin>>x;}while(x!='0'&&x!='1'&&x!='2');
    if(x=='0') {save(Cloud,filename1);exit(0);}
    return x;
}
void menu()
{
    char x;
    x=Menu();
    if(x=='1')
        menu1();
    else if(x=='2')
        menu2();
    else exit(1);
}

void menu1()
{
    system("cls");
    char route[8];
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-        生成指定路由器的路由表         -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t:->路由号(Rn): ";
    cin>>route;
    if(Cloud.Cheat(route)==true)
    {
        cout<<"没有此路由器!"<<endl;
    }
    else
    {
        Foutdata(Cloud,route);
    }
    system("pause");
    menu();
}

void menu2()
{
    system("cls");
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-            修改网络的拓扑             -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-          1.  去掉指定路由器           -"<<endl;
    cout<<"\t-          2.  去掉指定边               -"<<endl;
    cout<<"\t-          3.  加指定路由器             -"<<endl;
    cout<<"\t-          4.  加指定边                 -"<<endl;
    cout<<"\t-          0.  返回主菜单               -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t:-> _";
    char x;
    char route1[8],route2[8];
    do{cout<<"\b";cin>>x;}while(x!='0'&&x!='1'&&x!='2'&&x!='3'&&x!='4');
    cout<<endl;
    if(x=='0') menu();
    else if(x=='1')
    {
        cout<<"\t:->路由号(Rn): ";
        cin>>route1;
        if(Cloud.Cheat(route1)==true)
        {
            cout<<"\t原本就没有该路由器"<<endl;
        }
        else
        {
            if(Cloud.deleteVertex(route1))
                cout<<"\t路由器已删除";
        }
    }
    else if(x=='2')
    {
        cout<<"\t相邻两路由器(Rn): "<<endl;
        cout<<"\t:->一端  : ";
        cin>>route1;
        cout<<"\t:->另一端: ";
        cin>>route2;
        if(Cloud.Cheat_Edge(route1,route2)==true)//存在边
        {
            Cloud.deleteEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2));
        }
        else
        {
            cout<<"\t不存在此边"<<endl;
        }
    }
    else if(x=='3')
    {
        cout<<"\t:->路由号(Rn): ";
        cin>>route1;
        if(Cloud.Cheat(route1)==false)
        {
            cout<<"\t已经有该路由器"<<endl;
        }
        else
        {
            char network[10];
            cout<<"\t:->该路由器连接的网络(x.x.x.x): ";
            cin>>network;
            Cloud.insertVertex(route1, network);
        }
    }
    else if(x=='4')
    {
        cout<<"\t:->相邻两路由器(Rn):";
        cout<<"\t一端:";
        cin>>route1;
        cout<<"\t另一端:";
        cin>>route2;
        if(Cloud.Cheat_Edge(route1,route2)==true)
        {
            cout<<"\t此边已存在"<<endl;
        }
        else
        {
            int mertic;
            cout<<"\t:->度量: ";
            cin>>mertic;
            Cloud.insertEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2),mertic);
        }
    }
    system("pause");
    menu();
}

/*
void quit()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"-          1.  返回主菜单               -"<<endl;
    cout<<"-          2.  保存并退出               -"<<endl;
    cout<<"-----------------------------------------"<<endl;
    cout<<":-> _";
    char x;
    do{cout<<"\b";x=getche();}while(x!='1'&&x!='2');
    if(x=='1') menu();
    else if(x=='2')
    {
        save(Cloud,filename1);
        exit(0);
    }
}
*/
