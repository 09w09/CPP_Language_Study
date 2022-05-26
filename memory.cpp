#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef struct{
    int start;      //起始地址
    int lenght;     //长度
    int tag;        //标志,1分配，0没分配
}job_free;

typedef struct{
    char name[100]; //任务名字
    int start;      //起始地址
    int lenght;     //长度
}job_occupy;

void readData(vector<job_free> &jobs)
{
        // 以读模式打开文件
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
        //找到合适的分区
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

    cout << "请输入作业名和作业大小：" << endl;
    job_occupy job;
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);
    cin >> job.name >> job.lenght;
    assignMemory(jobs,process,job);

    cout << endl << "空闲分区表：" << endl;
    for (auto it : jobs)
    {
        cout << it.start << " " << it.lenght;
        if(it.tag==0)
            cout << " free" << endl;
        else
            cout << " occupy" << endl;
    }

    cout << endl << "已分分区表：" << endl;
    for (auto it : process)
    {
        cout << it.start << " " << it.lenght << " " << it.name << endl;
    }


    return 0;
}