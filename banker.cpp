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
    int pcount;             //进程数量（100个顶天）
    resouce_srt available;      //资源A、B、C的初始值
    vector<resouce_srt> request;   //各个进程请求资源的数量
    vector<resouce_srt> allocation;//各个进程已经分配到的资源的数量
    vector<resouce_srt> need;      //各个进程还需要的资源数量：request-allocation
    cout << "请输入进程数量：";cin >> pcount;
    cout << "请输入A、B、C的资源数：";cin >> available.A >> available.B >> available.C;
    cout << "请输入各进程的最大资源需求数" << endl << "进程   资源A   资源B   资源C" << endl;
    for(int i=0;i<pcount;i++)
    {
        cout << ">> P" << i+1 << " ";
        resouce_srt rt;
        cin >>  rt.A >> rt.B >> rt.C;
        request.push_back(rt);
    }
    cout << "请输入各进程的已分配的资源数" << endl << "进程   资源A   资源B   资源C" << endl;
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

        //第一步：计算资源还剩多少 
        available.A -= allocation[i].A;
        available.B -= allocation[i].B;
        available.C -= allocation[i].C;
    }

    printf("进程名\t请求资源\t已分配资源\t还需资源\n");
    for(int i=0;i<pcount;i++)
    {
        printf("%s    (%d,%d,%d)    (%d,%d,%d)    (%d,%d,%d)\n",need[i].name,
            request[i].A,request[i].B,request[i].C,
            allocation[i].A,allocation[i].B,allocation[i].C,
            need[i].A,need[i].B,need[i].C);
    }
    printf("当前剩余资源：(%d,%d,%d)\n",available.A,available.B,available.C);

    //第二步：探索分配资源序列
    cout << "资源分配安全序列：";
    while(need.size())
        for(int i=0;i<need.size();i++)
        {
            if(need[i].A <= available.A && 
                    need[i].B <= available.B && 
                            need[i].C <= available.C)
            {
                cout << need[i].name << " ";
                //进程用完后回收该资源
                available.A += allocation[i].A;
                available.B += allocation[i].B;
                available.C += allocation[i].C;
                need.erase(need.begin()+i);
                allocation.erase(allocation.begin()+i);
            }
        }


    return 0;
}