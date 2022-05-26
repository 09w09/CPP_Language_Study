#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PCB 
{
    //���³�Ա��֪
    char name ; //������
    int state ; //����״̬
    /*
        2������ʾ��ִ�С�״̬
        1������ʾ��������״̬
        0������ʾ��������״̬
    */
    int arriv_time; //���̵���ʱ��
    int cpu_time; //������Ҫ�� CPU ʱ��

    /////���³�Ա��ʼΪ�ա�
    int start_time; //��ʼ����ʱ��
    int finish_time; //���̽���ʱ��
    int waiting_time; //���̵ȴ�ʱ��
    int turnaround_time; //������תʱ��

    double weightturn_time; //���̴�Ȩ��תʱ��

    struct PCB* next;
 }Process_PCB;

void sortJobFirst(Process_PCB *phead,Process_PCB *pcurrent,int n)
{
    //��ǰֻ��һ������
    if(n==0)
    {
        phead->state = 2;
        phead->start_time = 0;
        phead->finish_time = phead->cpu_time + phead->start_time;   //���ʱ��=����ʱ��-��ʼʱ��
        phead->waiting_time = 0;
        phead->turnaround_time = phead->waiting_time + phead->cpu_time;
        phead->weightturn_time = double(phead->turnaround_time)/double(phead->cpu_time);
        return;
    }

    //�������ܷ���
    Process_PCB *q=phead,*qt=NULL;
    while(q!=NULL)
    {
        // //������Լ�������
        // if(pcurrent->name == q->name){
        //     qt=q;       //������һ��ָ��
        //     q=q->next;
        //     continue;
        // }
        // printf("\n66 %d-%d-%d 66\n",pcurrent->cpu_time,q->cpu_time,q->state);
        //�����ǰ����ʱ��������һ��ʱ�䣬���߶�ͷ��������,��������
        if(pcurrent->cpu_time > q->cpu_time || q->state==2){
            pcurrent->state = 1;                                                //����
            pcurrent->start_time = q->finish_time>pcurrent->arriv_time?q->finish_time:pcurrent->arriv_time;//��ʼʱ��=�ϸ��������ʱ��
            pcurrent->finish_time = pcurrent->cpu_time + pcurrent->start_time;  //���ʱ��=����ʱ��+��ʼʱ��
            pcurrent->waiting_time = q->finish_time - pcurrent->arriv_time;       //�ȴ�ʱ��=�ϸ��������ʱ��-����ʱ��
            pcurrent->turnaround_time = pcurrent->waiting_time + pcurrent->cpu_time;         //��תʱ��=����ʱ��+�ȴ�ʱ��
            pcurrent->weightturn_time = double(pcurrent->turnaround_time)/double(pcurrent->cpu_time);//��Ȩ��תʱ��=��תʱ��/����ʱ��
        
            //�ǲ嵽β�ͣ����ǲ嵽�м�
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
            //��ӣ���д���㵱ǰ�ڵ�
            q->start_time = q->start_time + pcurrent->cpu_time;     //��ʼʱ��=��ʼʱ��+��ӽ�������ʱ��
            q->finish_time = phead->cpu_time + phead->start_time;   //���ʱ��=����ʱ��-��ʼʱ��
            q->waiting_time = q->waiting_time + pcurrent->cpu_time; //�ȴ�ʱ��=�ȴ�ʱ��+���cpuʱ��
            q->turnaround_time = q->cpu_time + q->waiting_time ;    //��תʱ��=����ʱ��+�ȴ�ʱ��
            q->weightturn_time = double(q->turnaround_time)/double(q->cpu_time);
        }

        qt=q;       //������һ��ָ��
        q=q->next;
    }
}

int main()
{
    int n = 0,cur=0;  //�ܽ��̸�������ǰ���̸���
    printf("��������̸�����");
    scanf("%d",&n);
    //Process_PCB *process = (Process_PCB *)malloc(sizeof(Process_PCB)*n);
    //memset((char *)process,-1,sizeof(Process_PCB)*n);
    Process_PCB *phead = NULL,*ptail=NULL;  //������ִ�зŴ�β�ͣ���ִ�зŵ�ͷ��
    printf("�������������������ÿո����\n");
    printf("����״̬:\n\t2������ʾ ��ִ�С�״̬\n\t1������ʾ��������״̬\n\t0������ʾ��������״̬\n");
    printf("���̱�ʶ��������״̬������ʱ�䡢����ʱ��\n");
    for(cur=0;cur<n;cur++)
    {
        Process_PCB *process;
        //��ʼ��PCB�ռ�
        if(phead==NULL){ //�����һ��ִ��
            phead = (Process_PCB *)malloc(sizeof(Process_PCB));
            ptail = phead;
            process = phead;
        }else{          //����µĽڵ㣬��ʱ��ô����ȥ
            process = (Process_PCB *)malloc(sizeof(Process_PCB));      
            // process = ptail->next;
            // ptail = ptail->next;    //����β�ڵ�
        } 
        //�����û��������
        scanf(" %c %d %d %d",
                &process->name,
                &process->state,
                &process->arriv_time,
                &process->cpu_time);
        // printf("\n\n%d-%d-%d\n\n",process->state,process->arriv_time,process->cpu_time);
        process->next = NULL;
        //��������������
        sortJobFirst(phead,process,cur);
        //����β�ͽڵ�
        if(ptail->next!=NULL)
            ptail = ptail->next;    //����β�ڵ�
    }
    //��������й���Ϣ
    Process_PCB* q=phead;
    while(q!=NULL)
    {
            // q->start_time = q->next->finish_time;                   //��ʼʱ��=�ϸ��������ʱ��
            // q->finish_time = q->arriv_time - q->start_time;         //���ʱ��=����ʱ��-��ʼʱ��
            // q->waiting_time = q->next->finish_time - q->arriv_time;     //�ȴ�ʱ��=�ϸ��������ʱ��-����ʱ��
            // q->turnaround_time = q->waiting_time + q->cpu_time;         //��תʱ��=����ʱ��+�ȴ�ʱ��
            // q->weightturn_time = double(q->turnaround_time)/double(q->cpu_time);//��Ȩ��תʱ��=��תʱ��/����ʱ��

        printf("%c\n",q->name);
        printf("%d\n",q->state);
        printf("%d\n",q->arriv_time);
        printf("%d\n",q->cpu_time);

        printf("��ʼʱ�䣺%d\n",q->start_time);
        printf("���ʱ�䣺%d\n",q->finish_time);
        printf("�ȴ�ʱ�䣺%d\n",q->waiting_time);
        printf("��תʱ�䣺%d\n",q->turnaround_time);
        printf("��Ȩ��תʱ�䣺%f\n\n",q->weightturn_time);
        q=q->next;
    }  

    return 0;
}

