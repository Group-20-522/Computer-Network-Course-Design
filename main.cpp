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
{   manage();   //����·������ͼ
    menu();
    return 0;
}

char Menu() //�˵���ʽ
{
    system("cls");
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-       1.  ����ָ��·������·�ɱ�      -"<<endl;
    cout<<"\t-       2.  �޸����������              -"<<endl;
    cout<<"\t-       0.  ���沢�˳�                  -"<<endl;
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
    cout<<"\t-        ����ָ��·������·�ɱ�         -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t:->·�ɺ�(Rn): ";
    cin>>route;
    if(Cloud.Cheat(route)==true)
    {
        cout<<"û�д�·����!"<<endl;
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
    cout<<"\t-            �޸����������             -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t-          1.  ȥ��ָ��·����           -"<<endl;
    cout<<"\t-          2.  ȥ��ָ����               -"<<endl;
    cout<<"\t-          3.  ��ָ��·����             -"<<endl;
    cout<<"\t-          4.  ��ָ����                 -"<<endl;
    cout<<"\t-          0.  �������˵�               -"<<endl;
    cout<<"\t-----------------------------------------"<<endl;
    cout<<"\t:-> _";
    char x;
    char route1[8],route2[8];
    do{cout<<"\b";cin>>x;}while(x!='0'&&x!='1'&&x!='2'&&x!='3'&&x!='4');
    cout<<endl;
    if(x=='0') menu();
    else if(x=='1')
    {
        cout<<"\t:->·�ɺ�(Rn): ";
        cin>>route1;
        if(Cloud.Cheat(route1)==true)
        {
            cout<<"\tԭ����û�и�·����"<<endl;
        }
        else
        {
            if(Cloud.deleteVertex(route1))
                cout<<"\t·������ɾ��";
        }
    }
    else if(x=='2')
    {
        cout<<"\t������·����(Rn): "<<endl;
        cout<<"\t:->һ��  : ";
        cin>>route1;
        cout<<"\t:->��һ��: ";
        cin>>route2;
        if(Cloud.Cheat_Edge(route1,route2)==true)//���ڱ�
        {
            Cloud.deleteEdge(Cloud.getNodeDest(route1),Cloud.getNodeDest(route2));
        }
        else
        {
            cout<<"\t�����ڴ˱�"<<endl;
        }
    }
    else if(x=='3')
    {
        cout<<"\t:->·�ɺ�(Rn): ";
        cin>>route1;
        if(Cloud.Cheat(route1)==false)
        {
            cout<<"\t�Ѿ��и�·����"<<endl;
        }
        else
        {
            char network[10];
            cout<<"\t:->��·�������ӵ�����(x.x.x.x): ";
            cin>>network;
            Cloud.insertVertex(route1, network);
        }
    }
    else if(x=='4')
    {
        cout<<"\t:->������·����(Rn):";
        cout<<"\tһ��:";
        cin>>route1;
        cout<<"\t��һ��:";
        cin>>route2;
        if(Cloud.Cheat_Edge(route1,route2)==true)
        {
            cout<<"\t�˱��Ѵ���"<<endl;
        }
        else
        {
            int mertic;
            cout<<"\t:->����: ";
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
    cout<<"-          1.  �������˵�               -"<<endl;
    cout<<"-          2.  ���沢�˳�               -"<<endl;
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
