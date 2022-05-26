#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;

//PCB节点信息
class PCBInfo
{
public:
    PCBInfo(char n,int s,int ar,int ct)
    : name(n),state(s),arriv_time(ar),cpu_time(ct)
    {
        worked_time = 0;
        start_time = 0;
        finish_time = 0;
        turnaround_time = 0;

        weightturn_time = 0;
    }
    PCBInfo(){}
    PCBInfo(const PCBInfo& c)
    {       
        name = c.name;
        state = c.state;
        arriv_time = c.arriv_time;
        cpu_time = c.cpu_time;


        worked_time = c.worked_time;
        start_time = c.start_time;
        finish_time = c.finish_time;
        turnaround_time = c.turnaround_time;
        weightturn_time = c.weightturn_time;
    }
    
    //计算马上执行程序数据
    bool run(int ct)
    {
        start_time = (start_time==0)?ct:start_time;   
        worked_time++;
        if(worked_time>=cpu_time)
            return true;    //进程已完成
        else
            return false;   //进程未完成
    }
    //打印时序图
    void printGraph(int ct)
    {
        for(int i=0;i<ct;i++)
            printf("  ");
        printf("%c-\n",name);
    }
    //进程完成执行，计算进程相关数据
    void finish(int t)
    {
        finish_time = t;
        turnaround_time = finish_time - arriv_time;
        weightturn_time = double(turnaround_time)/double(cpu_time);
    }

    //打印输出数据
    void print()
    {
        printf("%c\n",name);
        printf("%d\n",state);
        printf("%d\n",arriv_time);
        printf("%d\n",cpu_time);

        printf("开始时间：%d\n",start_time);
        printf("完成时间：%d\n",finish_time);
        printf("运行时间：%d\n",cpu_time);
        printf("周转时间：%d\n",turnaround_time);
        printf("带权周转时间：%f\n\n",weightturn_time);
    }

    void print2()
    {
        printf("%c\t%d\t%d\t\t%d\t%d\t%d\n",
            name,start_time,finish_time,
            arriv_time,turnaround_time,weightturn_time);
    }

    int getArriveTime(){ return arriv_time; }
    double getWeightturnTime(){ return weightturn_time; }

private:
    //以下成员已知
    char name ;         //进程名
    int state ;         //进程状态
    int arriv_time;     //进程到达时间
    int cpu_time;       //运行需要的 CPU 时间

    /////以下成员初始为空。
    int worked_time;    //已运行时间
    int start_time;     //开始运行时间
    int finish_time;    //进程结束时间
    int turnaround_time;//进程周转时间
    double weightturn_time;//进程带权周转时间
    /*
    state:
        2——表示“执行”状态
        1——表示“就绪”状态
        0——表示“阻塞”状态
    */
friend
    bool operator>(const PCBInfo &l,const PCBInfo &r) 
    {
        return l.arriv_time>r.arriv_time;   //从大到小排序
    }
};

int main()
{
    int n=5;      //就绪进程数
    int m=0;      //阻塞进程数
    int tim=1;    //时间片
    int num=10;    //系统定时唤醒阻塞进程的时间间隔
    PCBInfo current;
    queue<PCBInfo> readyList;
    queue<PCBInfo> blockList; 
    vector<PCBInfo> okList;
    priority_queue<PCBInfo,vector<PCBInfo>,greater<PCBInfo> > processList;    //输入进程队列

    cout << "请输入进程个数：";cin >> n;
    cout << "请输入阻塞个数：";cin >> m;
    cout << "请输入时间片：";cin >> tim;
    cout << "请输入唤醒阻塞进程间隔时间：";cin >> num;
    cout << "请依次输入以下内容用空格隔开" << endl;
    cout << "进程状态:\n\t2——表示 “执行”状态\n\t1——表示“就绪”状态\n\t0——表示“阻塞”状态" << endl;
    cout << "进程标识符、进程状态、到达时间、服务时间" << endl;
    
    int aa[5][4] = {
        {'a',1,0,4},
        {'b',1,1,3},
        {'c',1,2,4},
        {'d',1,3,2},
        {'e',1,4,4},
    };
    
    
    for(int i=0;i<n;i++)
    {
        char a;
        int b,c,d;
        //cin >> a >> b >> c >> d;
        a = aa[i][0];
        b = aa[i][1];
        c = aa[i][2];
        d = aa[i][3];
        printf("%c %d %d %d\n",a,b,c,d);
        //开始时间为0
        if(c==0)    
            current = PCBInfo(a,b,c,d);
        else
            processList.push(PCBInfo(a,b,c,d));
    }

    cout << "##############进程时序图###############" << endl;
    cout << "0 1 2 3 4 5 6 7 8 9 101112131415161718" << endl;

    int ct=0;               //当前时间搓
    PCBInfo q;              //临时变量
    int finished = 0;       //以及完成的进程数量
    bool isfinish = false;  //当前运行进程是否完成
    do{
        //运行当前进程
        isfinish = current.run(ct);   
        current.printGraph(ct);
        ct++;
        //查看有没有新进程到达，有的话加入就绪队列
        if(processList.size()>0){
            q = processList.top();
            if(q.getArriveTime()==ct){
                readyList.push(q);
                processList.pop();
            }
        }     
        //如果当前进程没有完成，放入准备队列继续
        if(!isfinish){
            readyList.push(current);
        }else{
            finished++;
            current.finish(ct);
            okList.push_back(current);
        }
        //从就绪队列取出一个数据，下一轮时间片继续执行
        current = readyList.front();
        readyList.pop();
    }while(finished<n);

    //输出缓存的进程信息
    double ttime=0.0;
    printf("\n进程、开始时间、完成时间、到达时间、周转时间、带权周转时间\n");
    for(int i=0;i<okList.size();i++)
    {
        okList.at(i).print2();
        ttime+=okList.at(i).getWeightturnTime();
    }
    printf("系统平均带权周转时间：%lf",ttime/okList.size());

    return 0;
}
