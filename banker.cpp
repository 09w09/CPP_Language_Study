#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
   char name[3]; 
   int A;
   int B;
   int C;
}resouce_srt;

int main()
{
    int pcount;             //����������100�����죩
    resouce_srt available;      //��ԴA��B��C�ĳ�ʼֵ
    vector<resouce_srt> request;   //��������������Դ������
    vector<resouce_srt> allocation;//���������Ѿ����䵽����Դ������
    vector<resouce_srt> need;      //�������̻���Ҫ����Դ������request-allocation
    cout << "���������������";cin >> pcount;
    cout << "������A��B��C����Դ����";cin >> available.A >> available.B >> available.C;
    cout << "����������̵������Դ������" << endl << "����   ��ԴA   ��ԴB   ��ԴC" << endl;
    for(int i=0;i<pcount;i++)
    {
        cout << ">> P" << i+1 << " ";
        resouce_srt rt;
        cin >>  rt.A >> rt.B >> rt.C;
        request.push_back(rt);
    }
    cout << "����������̵��ѷ������Դ��" << endl << "����   ��ԴA   ��ԴB   ��ԴC" << endl;
    for(int i=0;i<pcount;i++)
    {
        cout << ">> P" << i+1 << " ";
        resouce_srt rt1,rt2;
        cin >>  rt1.A >> rt1.B >> rt1.C;
        allocation.push_back(rt1);
      
        rt2.name[0] = 'P';
        rt2.name[1] = i+1 + '0';
        rt2.name[2] = '\0';
        rt2.A = request[i].A - allocation[i].A;
        rt2.B = request[i].B - allocation[i].B;
        rt2.C = request[i].C - allocation[i].C;
        need.push_back(rt2);

        //��һ����������Դ��ʣ���� 
        available.A -= allocation[i].A;
        available.B -= allocation[i].B;
        available.C -= allocation[i].C;
    }

    printf("������\t������Դ\t�ѷ�����Դ\t������Դ\n");
    for(int i=0;i<pcount;i++)
    {
        printf("%s    (%d,%d,%d)    (%d,%d,%d)    (%d,%d,%d)\n",need[i].name,
            request[i].A,request[i].B,request[i].C,
            allocation[i].A,allocation[i].B,allocation[i].C,
            need[i].A,need[i].B,need[i].C);
    }
    printf("��ǰʣ����Դ��(%d,%d,%d)\n",available.A,available.B,available.C);

    //�ڶ�����̽��������Դ����
    cout << "��Դ���䰲ȫ���У�";
    while(need.size())
        for(int i=0;i<need.size();i++)
        {
            if(need[i].A <= available.A && 
                    need[i].B <= available.B && 
                            need[i].C <= available.C)
            {
                cout << need[i].name << " ";
                //�����������ո���Դ
                available.A += allocation[i].A;
                available.B += allocation[i].B;
                available.C += allocation[i].C;
                need.erase(need.begin()+i);
                allocation.erase(allocation.begin()+i);
            }
        }


    return 0;
}