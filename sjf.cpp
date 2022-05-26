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
        //��ǰ������
        is_empty = false;
    }
    bool isEmpty(){return is_empty;}
    // void setEmpty(bool b){ is_empty=b;}
    //��������ִ�г�������
    void calFirstData()
    {
        start_time = 0;
        finish_time = cpu_time + start_time;   //���ʱ��=����ʱ��-��ʼʱ��
        waiting_time = 0;
        turnaround_time = waiting_time + cpu_time;
        weightturn_time = double(turnaround_time)/double(cpu_time);
    }
    //������������Ŷ�����
    void calDataWith(const PCBInfo& pcbinfo)
    {            
        start_time = max(pcbinfo.finish_time,arriv_time);       //��ʼʱ��=�ϸ��������ʱ��/��ǰ���̿�ʼʱ��
        finish_time = cpu_time + start_time;                    //���ʱ��=����ʱ��-��ʼʱ��
        waiting_time = pcbinfo.finish_time - arriv_time;        //�ȴ�ʱ��=�ϸ��������ʱ��-����ʱ��
        turnaround_time = waiting_time + cpu_time;              //��תʱ��=����ʱ��+�ȴ�ʱ��
        weightturn_time = double(turnaround_time)/double(cpu_time); //��Ȩ��תʱ��=��תʱ��/����ʱ��

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
        printf("�ȴ�ʱ�䣺%d\n",waiting_time);
        printf("����ʱ�䣺%d\n",cpu_time);
        printf("��תʱ�䣺%d\n",turnaround_time);
        printf("��Ȩ��תʱ�䣺%f\n\n",weightturn_time);
    }
    //ͼ�λ���ӡ
    void printGraph()
    {
        int i;
        //��ӡ�ո�
        for(i=0;i<start_time;i++)
            cout << "  ";

        //��ӡ����ʱ��
        for(i=0;i<cpu_time;i++)
            cout << "--";
        
        cout << name << endl;
    }

private:
    bool is_empty;      //��ǰ�Ƿ�������
    //���³�Ա��֪
    char name ;         //������
    int state ;         //����״̬
    int arriv_time;     //���̵���ʱ��
    int cpu_time;       //������Ҫ�� CPU ʱ��

    /////���³�Ա��ʼΪ�ա�
    int start_time;     //��ʼ����ʱ��
    int finish_time;    //���̽���ʱ��
    int waiting_time;   //���̵ȴ�ʱ��
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
        return l.cpu_time>r.cpu_time;   //�Ӵ�С����
    }

};

int main()
{
    int n;
    PCBInfo current;
    vector<PCBInfo> pcblist;
    priority_queue<PCBInfo,vector<PCBInfo>,greater<PCBInfo> > queue;    //���ȶ��У�С���ѣ���CPUʱ���Ϊ����
    
    cout << "��������̸�����";cin >> n;
    cout << "�������������������ÿո����" << endl;
    cout << "����״̬:\n\t2������ʾ ��ִ�С�״̬\n\t1������ʾ��������״̬\n\t0������ʾ��������״̬" << endl;
    cout << "���̱�ʶ��������״̬������ʱ�䡢����ʱ��" << endl;
    for(int i=0;i<n;i++)
    {
        char a;
        int b,c,d;
        cin >> a >> b >> c >> d;
        //��ʼʱ��Ϊ0
        if(c==0)    
            current = PCBInfo(a,b,c,d);
        else
            queue.push(PCBInfo(a,b,c,d));
    }

    cout << "##############����ʱ��ͼ###############" << endl;
    cout << "0 1 2 3 4 5 6 7 8 9 101112131415161718" << endl;

    //��ǰ���еĳ���
    current.calFirstData();
    current.printGraph();

    PCBInfo last,q; //һ������������һ���ڵ㣬��������ǰ�ڵ�
    while(queue.size())
    {
        //�ӶѶ�ȡ��һ���ڵ�
        q = queue.top();
        queue.pop();
        //�������ǰ���������Ϣ
        if(last.isEmpty()){
            q.calDataWith(current);
        }else{
            q.calDataWith(last);
        }
        //��ӡ����ͼ��
        q.printGraph();
        //���ݵ�ǰ�ڵ�
        last = q;
    }

    return 0;
}
