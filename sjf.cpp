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
        is_empty = false;
        start_time = 0;
        finish_time = 0;
        waiting_time = 0;
        turnaround_time = 0;

        weightturn_time = 0;
    }
    PCBInfo() : is_empty(true){}
    PCBInfo(const PCBInfo& c)
    {       
        name = c.name;
        state = c.state;
        arriv_time = c.arriv_time;
        cpu_time = c.cpu_time;

        start_time = c.start_time;
        finish_time = c.finish_time;
        waiting_time = c.waiting_time;
        turnaround_time = c.turnaround_time;
        weightturn_time = c.weightturn_time;
        //当前有数据
        is_empty = false;
    }
    bool isEmpty(){return is_empty;}
    // void setEmpty(bool b){ is_empty=b;}
    //计算马上执行程序数据
    void calFirstData()
    {
        start_time = 0;
        finish_time = cpu_time + start_time;   //完成时间=到达时间-开始时间
        waiting_time = 0;
        turnaround_time = waiting_time + cpu_time;
        weightturn_time = double(turnaround_time)/double(cpu_time);
    }
    //计算最短优先排队数据
    void calDataWith(const PCBInfo& pcbinfo)
    {            
        start_time = max(pcbinfo.finish_time,arriv_time);       //开始时间=上个进程完成时间/当前进程开始时间
        finish_time = cpu_time + start_time;                    //完成时间=到达时间-开始时间
        waiting_time = pcbinfo.finish_time - arriv_time;        //等待时间=上个进程完成时间-到达时间
        turnaround_time = waiting_time + cpu_time;              //周转时间=运行时间+等待时间
        weightturn_time = double(turnaround_time)/double(cpu_time); //带权周转时间=周转时间/运行时间

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
        printf("等待时间：%d\n",waiting_time);
        printf("运行时间：%d\n",cpu_time);
        printf("周转时间：%d\n",turnaround_time);
        printf("带权周转时间：%f\n\n",weightturn_time);
    }
    //图形化打印
    void printGraph()
    {
        int i;
        //打印空格
        for(i=0;i<start_time;i++)
            cout << "  ";

        //打印运行时间
        for(i=0;i<cpu_time;i++)
            cout << "--";
        
        cout << name << endl;
    }

private:
    bool is_empty;      //当前是否有数据
    //以下成员已知
    char name ;         //进程名
    int state ;         //进程状态
    int arriv_time;     //进程到达时间
    int cpu_time;       //运行需要的 CPU 时间

    /////以下成员初始为空。
    int start_time;     //开始运行时间
    int finish_time;    //进程结束时间
    int waiting_time;   //进程等待时间
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
        return l.cpu_time>r.cpu_time;   //从大到小排序
    }

};

int main()
{
    int n;
    PCBInfo current;
    vector<PCBInfo> pcblist;
    priority_queue<PCBInfo,vector<PCBInfo>,greater<PCBInfo> > queue;    //优先队列，小顶堆，以CPU时间短为优先
    
    cout << "请输入进程个数：";cin >> n;
    cout << "请依次输入以下内容用空格隔开" << endl;
    cout << "进程状态:\n\t2——表示 “执行”状态\n\t1——表示“就绪”状态\n\t0——表示“阻塞”状态" << endl;
    cout << "进程标识符、进程状态、到达时间、服务时间" << endl;
    for(int i=0;i<n;i++)
    {
        char a;
        int b,c,d;
        cin >> a >> b >> c >> d;
        //开始时间为0
        if(c==0)    
            current = PCBInfo(a,b,c,d);
        else
            queue.push(PCBInfo(a,b,c,d));
    }

    cout << "##############进程时序图###############" << endl;
    cout << "0 1 2 3 4 5 6 7 8 9 101112131415161718" << endl;

    //当前运行的程序
    current.calFirstData();
    current.printGraph();

    PCBInfo last,q; //一个用来备份上一个节点，和索引当前节点
    while(queue.size())
    {
        //从堆顶取出一个节点
        q = queue.top();
        queue.pop();
        //计算出当前进程相关信息
        if(last.isEmpty()){
            q.calDataWith(current);
        }else{
            q.calDataWith(last);
        }
        //打印进程图形
        q.printGraph();
        //备份当前节点
        last = q;
    }

    return 0;
}
