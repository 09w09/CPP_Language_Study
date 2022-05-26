#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef struct{
    int start;      //��ʼ��ַ
    int lenght;     //����
    int tag;        //��־,1���䣬0û����
}job_free;

typedef struct{
    char name[100]; //��������
    int start;      //��ʼ��ַ
    int lenght;     //����
}job_occupy;

void readData(vector<job_free> &jobs)
{
        // �Զ�ģʽ���ļ�
   ifstream infile; 
   infile.open("mem.txt"); 

    while (!infile.eof())
    {
        char data1[100],data2[100];
        infile >> data1 >> data2;
        cout << data1 << " " << data2 << endl;

        job_free jb;
        jb.start = atoi(data1);
        jb.lenght = atoi(data2);
        jb.tag = 0;
        
        if(jobs.size()>0){
            int i=0;
            for (auto it : jobs)
            {
                if(it.lenght>jb.lenght){
                    jobs.insert(jobs.begin()+i,jb);
                    goto over;
                }
                i++;
            }    
        } 
        jobs.push_back(jb);
        over:;
    }

    infile.close();
}

void assignMemory(vector<job_free> &jobs,vector<job_occupy> &process,job_occupy &job)
{
    int i=0;
    for (auto it : jobs)
    {
        //�ҵ����ʵķ���
        if(it.lenght>job.lenght){
            jobs.at(i).lenght =  it.lenght - job.lenght;
            job.start = jobs.at(i).start + jobs.at(i).lenght;
            process.push_back(job);
            break;
        }else if(it.lenght==job.lenght){
            job.start = it.start;
            process.push_back(job);
            jobs.erase(jobs.begin()+i);
            break;
        }
        i++;
    }    
}

int main()
{
    vector<job_free> jobs;
    vector<job_occupy> process;
    readData(jobs);

    cout << "��������ҵ������ҵ��С��" << endl;
    job_occupy job;
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);

    cout << endl << "���з�����" << endl;
    for (auto it : jobs)
    {
        cout << it.start << " " << it.lenght;
        if(it.tag==0)
            cout << " free" << endl;
        else
            cout << " occupy" << endl;
    }

    cout << endl << "�ѷַ�����" << endl;
    for (auto it : process)
    {
        cout << it.start << " " << it.lenght << " " << it.name << endl;
    }


    return 0;
}