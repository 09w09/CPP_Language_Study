#include <iostream>
#include <queue>
#include <vector>
#include <limits>
using namespace std;

//PCB�ڵ���Ϣ
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
    
    //��������ִ�г�������
    bool run(int ct)
    {
        start_time = (start_time==0)?ct:start_time;   
        worked_time++;
        if(worked_time>=cpu_time)
            return true;    //���������
        else
            return false;   //����δ���
    }
    //��ӡʱ��ͼ
    void printGraph(int ct)
    {
        for(int i=0;i<ct;i++)
            printf("  ");
        printf("%c-\n",name);
    }
    //�������ִ�У���������������
    void finish(int t)
    {
        finish_time = t;
        turnaround_time = finish_time - arriv_time;
        weightturn_time = double(turnaround_time)/double(cpu_time);
    }

    //��ӡ�������
    void print()
    {
        printf("%c\n",name);
        printf("%d\n",state);
        printf("%d\n",arriv_time);
        printf("%d\n",cpu_time);

        printf("��ʼʱ�䣺%d\n",start_time);
        printf("���ʱ�䣺%d\n",finish_time);
        printf("����ʱ�䣺%d\n",cpu_time);
        printf("��תʱ�䣺%d\n",turnaround_time);
        printf("��Ȩ��תʱ�䣺%f\n\n",weightturn_time);
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
    //���³�Ա��֪
    char name ;         //������
    int state ;         //����״̬
    int arriv_time;     //���̵���ʱ��
    int cpu_time;       //������Ҫ�� CPU ʱ��

    /////���³�Ա��ʼΪ�ա�
    int worked_time;    //������ʱ��
    int start_time;     //��ʼ����ʱ��
    int finish_time;    //���̽���ʱ��
    int turnaround_time;//������תʱ��
    double weightturn_time;//���̴�Ȩ��תʱ��
    /*
    state:
        2������ʾ��ִ�С�״̬
        1������ʾ��������״̬
        0������ʾ��������״̬
    */
friend
    bool operator>(const PCBInfo &l,const PCBInfo &r) 
    {
        return l.arriv_time>r.arriv_time;   //�Ӵ�С����
    }
};

int main()
{
    int n=5;      //����������
    int m=0;      //����������
    int tim=1;    //ʱ��Ƭ
    int num=10;    //ϵͳ��ʱ�����������̵�ʱ����
    PCBInfo current;
    queue<PCBInfo> readyList;
    queue<PCBInfo> blockList; 
    vector<PCBInfo> okList;
    priority_queue<PCBInfo,vector<PCBInfo>,greater<PCBInfo> > processList;    //������̶���

    cout << "��������̸�����";cin >> n;
    cout << "����������������";cin >> m;
    cout << "������ʱ��Ƭ��";cin >> tim;
    cout << "�����뻽���������̼��ʱ�䣺";cin >> num;
    cout << "�������������������ÿո����" << endl;
    cout << "����״̬:\n\t2������ʾ ��ִ�С�״̬\n\t1������ʾ��������״̬\n\t0������ʾ��������״̬" << endl;
    cout << "���̱�ʶ��������״̬������ʱ�䡢����ʱ��" << endl;
    
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
        //��ʼʱ��Ϊ0
        if(c==0)    
            current = PCBInfo(a,b,c,d);
        else
            processList.push(PCBInfo(a,b,c,d));
    }

    cout << "##############����ʱ��ͼ###############" << endl;
    cout << "0 1 2 3 4 5 6 7 8 9 101112131415161718" << endl;

    int ct=0;               //��ǰʱ���
    PCBInfo q;              //��ʱ����
    int finished = 0;       //�Լ���ɵĽ�������
    bool isfinish = false;  //��ǰ���н����Ƿ����
    do{
        //���е�ǰ����
        isfinish = current.run(ct);   
        current.printGraph(ct);
        ct++;
        //�鿴��û���½��̵���еĻ������������
        if(processList.size()>0){
            q = processList.top();
            if(q.getArriveTime()==ct){
                readyList.push(q);
                processList.pop();
            }
        }     
        //�����ǰ����û����ɣ�����׼�����м���
        if(!isfinish){
            readyList.push(current);
        }else{
            finished++;
            current.finish(ct);
            okList.push_back(current);
        }
        //�Ӿ�������ȡ��һ�����ݣ���һ��ʱ��Ƭ����ִ��
        current = readyList.front();
        readyList.pop();
    }while(finished<n);

    //�������Ľ�����Ϣ
    double ttime=0.0;
    printf("\n���̡���ʼʱ�䡢���ʱ�䡢����ʱ�䡢��תʱ�䡢��Ȩ��תʱ��\n");
    for(int i=0;i<okList.size();i++)
    {
        okList.at(i).print2();
        ttime+=okList.at(i).getWeightturnTime();
    }
    printf("ϵͳƽ����Ȩ��תʱ�䣺%lf",ttime/okList.size());

    return 0;
}
