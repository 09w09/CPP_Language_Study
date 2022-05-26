#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PCB 
{
    //以下成员已知
    char name ; //进程名
    int state ; //进程状态
    /*
        2——表示“执行”状态
        1——表示“就绪”状态
        0——表示“阻塞”状态
    */
    int arriv_time; //进程到达时间
    int cpu_time; //运行需要的 CPU 时间

    /////以下成员初始为空。
    int start_time; //开始运行时间
    int finish_time; //进程结束时间
    int waiting_time; //进程等待时间
    int turnaround_time; //进程周转时间

    double weightturn_time; //进程带权周转时间

    struct PCB* next;
 }Process_PCB;

void sortJobFirst(Process_PCB *phead,Process_PCB *pcurrent,int n)
{
    //当前只有一个进程
    if(n==0)
    {
        phead->state = 2;
        phead->start_time = 0;
        phead->finish_time = phead->cpu_time + phead->start_time;   //完成时间=到达时间-开始时间
        phead->waiting_time = 0;
        phead->turnaround_time = phead->waiting_time + phead->cpu_time;
        phead->weightturn_time = double(phead->turnaround_time)/double(phead->cpu_time);
        return;
    }

    //遍历看能否插队
    Process_PCB *q=phead,*qt=NULL;
    while(q!=NULL)
    {
        // //如果是自己就跳过
        // if(pcurrent->name == q->name){
        //     qt=q;       //备份上一个指针
        //     q=q->next;
        //     continue;
        // }
        // printf("\n66 %d-%d-%d 66\n",pcurrent->cpu_time,q->cpu_time,q->state);
        //如果当前进程时间大于最后一个时间，或者对头正在运行,不允许插队
        if(pcurrent->cpu_time > q->cpu_time || q->state==2){
            pcurrent->state = 1;                                                //就绪
            pcurrent->start_time = q->finish_time>pcurrent->arriv_time?q->finish_time:pcurrent->arriv_time;//开始时间=上个进程完成时间
            pcurrent->finish_time = pcurrent->cpu_time + pcurrent->start_time;  //完成时间=到达时间+开始时间
            pcurrent->waiting_time = q->finish_time - pcurrent->arriv_time;       //等待时间=上个进程完成时间-到达时间
            pcurrent->turnaround_time = pcurrent->waiting_time + pcurrent->cpu_time;         //周转时间=运行时间+等待时间
            pcurrent->weightturn_time = double(pcurrent->turnaround_time)/double(pcurrent->cpu_time);//带权周转时间=周转时间/运行时间
        
            //是插到尾巴，还是插到中间
            if(qt==NULL)
            {
                // printf("\n4444\n");
                phead->next = pcurrent;
                break;
            }else{
                printf("\n5555\n");
                qt->next = pcurrent;
                pcurrent->next = q;
                break;
            }
        }else{
            //插队，重写计算当前节点
            q->start_time = q->start_time + pcurrent->cpu_time;     //开始时间=开始时间+插队进程运行时间
            q->finish_time = phead->cpu_time + phead->start_time;   //完成时间=到达时间-开始时间
            q->waiting_time = q->waiting_time + pcurrent->cpu_time; //等待时间=等待时间+插队cpu时间
            q->turnaround_time = q->cpu_time + q->waiting_time ;    //周转时间=运行时间+等待时间
            q->weightturn_time = double(q->turnaround_time)/double(q->cpu_time);
        }

        qt=q;       //备份上一个指针
        q=q->next;
    }
}

int main()
{
    int n = 0,cur=0;  //总进程个数，当前进程个数
    printf("请输入进程个数：");
    scanf("%d",&n);
    //Process_PCB *process = (Process_PCB *)malloc(sizeof(Process_PCB)*n);
    //memset((char *)process,-1,sizeof(Process_PCB)*n);
    Process_PCB *phead = NULL,*ptail=NULL;  //链表先执行放大尾巴，后执行放到头部
    printf("请依次输入以下内容用空格隔开\n");
    printf("进程状态:\n\t2——表示 “执行”状态\n\t1——表示“就绪”状态\n\t0——表示“阻塞”状态\n");
    printf("进程标识符、进程状态、到达时间、服务时间\n");
    for(cur=0;cur<n;cur++)
    {
        Process_PCB *process;
        //初始化PCB空间
        if(phead==NULL){ //如果第一次执行
            phead = (Process_PCB *)malloc(sizeof(Process_PCB));
            ptail = phead;
            process = phead;
        }else{          //添加新的节点，此时还么放上去
            process = (Process_PCB *)malloc(sizeof(Process_PCB));      
            // process = ptail->next;
            // ptail = ptail->next;    //更新尾节点
        } 
        //接收用户输入进程
        scanf(" %c %d %d %d",
                &process->name,
                &process->state,
                &process->arriv_time,
                &process->cpu_time);
        // printf("\n\n%d-%d-%d\n\n",process->state,process->arriv_time,process->cpu_time);
        process->next = NULL;
        //计算进程相关数据
        sortJobFirst(phead,process,cur);
        //更新尾巴节点
        if(ptail->next!=NULL)
            ptail = ptail->next;    //更新尾节点
    }
    //输出进程有关信息
    Process_PCB* q=phead;
    while(q!=NULL)
    {
            // q->start_time = q->next->finish_time;                   //开始时间=上个进程完成时间
            // q->finish_time = q->arriv_time - q->start_time;         //完成时间=到达时间-开始时间
            // q->waiting_time = q->next->finish_time - q->arriv_time;     //等待时间=上个进程完成时间-到达时间
            // q->turnaround_time = q->waiting_time + q->cpu_time;         //周转时间=运行时间+等待时间
            // q->weightturn_time = double(q->turnaround_time)/double(q->cpu_time);//带权周转时间=周转时间/运行时间

        printf("%c\n",q->name);
        printf("%d\n",q->state);
        printf("%d\n",q->arriv_time);
        printf("%d\n",q->cpu_time);

        printf("开始时间：%d\n",q->start_time);
        printf("完成时间：%d\n",q->finish_time);
        printf("等待时间：%d\n",q->waiting_time);
        printf("周转时间：%d\n",q->turnaround_time);
        printf("带权周转时间：%f\n\n",q->weightturn_time);
        q=q->next;
    }  

    return 0;
}

