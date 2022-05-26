#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;

#define MAX_TEMP 100

typedef struct
{
    int id;
    char text[MAX_TEMP];
}word;


//�����ֱ�
static char reserveWord[32][MAX_TEMP] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
//��������
static char operatorOrDelimiter[36][10] = {
   "+","-","*","/","<","<=",">",">=","=","==",
   "!=",";","(",")","^",",","\"","\'","#","&",
   "&&","|","||","%","~","<<",">>","[","]","{",
   "}","\\",".","\?",":","!"
};

//��ʶ����
// static  char IDentifierTbl[1000][50] = {""};

static word idtable[1000];

//�ж��Ƿ�Ϊ����
bool isDigit(char ch)
{
    if(ch>= '0' && ch <= '9')
        return true;
    return false;
}

//�ж��Ƿ�Ϊ��ĸ���»���
bool isLetter(char ch)
{
    if((ch>= 'a' && ch<='z') || ( ch <= 'Z' && ch >= 'A')|| ch == '_')
        return true;
    return false;
}

//�ж��Ƿ�Ϊ������
int isReserve(char *s)
{   
    for(int i=0;i<32;++i)
    {
        if(strcmp(reserveWord[i],s) == 0)
            return i+1;//�����ֱ���
    }
    return -1;    
}
//Դ����Ԥ��������ע�ͺͻ��лس��Ʊ��
void filter(char *s,int len)
{
    char tmp[10000];
    int p = 0;
    for(int i=0;i<len;++i)
    {
        if(s[i] == '/' && s[i+1] == '/')//����ע��
        {
            while(s[i++]!='\n')i;//ɨ�赽���з�Ϊֹ
        }
        if(s[i] == '/' && s[i+1] == '*')//����ע��
        {
            i+=2;
            while(s[i] != '*' && s[i+1] != '/')
            {
                if(s[i] == '\0')
                {
                    cout<<"annotation error!"<<endl;
                    exit(0);
                }
                i++;
            }
            i+=2;
        }//ȥ�������
        if(s[i] != '\n' && s[i] != '\t' && s[i] != '\v' && s[i] != '\r')
        {
            tmp[p++] = s[i];
        }
        // ����ո��Ϊһ��
        // if(s[i] == ' ')
        // {
        //     while (s[i]==' ') ++i;
        //     tmp[p++] = ' ';     
        // }
    }
    tmp[p] = '\0';
    strcpy(s,tmp);
}

//ɨ��Դ����syn���ֱ��룬token�ǵ�ǰɨ��ĵ��ʣ�pΪɨ��λ������
void scanner(int &syn,char * project,char * token,int &p)
{   
    int count = 0;
    char ch;
    ch = project[p];
    while(ch == ' ')//ȥ���ո�
    {
        ++p;
        ch = project[p];
    }
    for(int i=0;i<MAX_TEMP;i++)//���token
    {
        token[i] = '\0';
    }
    //����ĸ��ͷ
    if(isLetter(project[p]))
    {
        token[count++] = project[p++];
        while(isLetter(project[p])||isDigit(project[p]))//��������ĸ������
        {
            token[count++] = project[p++];
        }
        token[count] = '\0';
        syn = isReserve(token);//��ʶ���ֱ��룺�ؼ��֣�1~32��
        if(syn == -1)
        {//�����Ǳ��������Ǳ�ʶ��
            syn = 100;//��ʶ���ֱ��룺�Ǳ����ؼ���
        }
        return;
    }
    //�����ֿ�ͷ
    else if(isDigit(project[p]))
    {
       token[count++] = project[p++]; 
       while(isDigit(project[p]))//����������
        {
            token[count++] = project[p++];
        }
        token[count] = '\0';
        syn = 99;//��ʶ���ֱ��룺���ֳ���
        return;
    }
    //�ַ�
    else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
            || ch == ',' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
            || ch == ']' || ch == '{' || ch == '}' || ch == '.' || ch == '\?' || ch == ':')
    {
        token[count++] = project[p++];
        token[count] = '\0';
        for(int i=0;i<36;++i)
        {
            if(strcmp(operatorOrDelimiter[i],token) == 0)
            {
                syn = 33+i;//��ʶ���ֱ��룺���ţ�33~68��
                break;
            }
        }
        return;
    }
    //�ַ�������
    else if(ch == '\"')
    {
        token[count++] = project[p++];
        char c;
        while(!(project[p]=='\"' && project[p-1]!='\\'))//��˫���Ž�β
        {
            c = project[p];
            token[count++] = project[p++];
        }
        token[count++] = project[p++];
        token[count] = '\0';
        syn = 101;  //��ʶ���ֱ��룺�ַ�������
        return;
    }
    else if(ch == '<')
    {//������< <= <<
        ++p;
        if(project[p] == '=')//<=
        {
            syn = 38;//��ʶ���ֱ��룺����<=
        }
        if(project[p] == '<')//<<
        {
            syn = 58;//��ʶ���ֱ��룺����<<
        }
        else//<
        {
            --p;
            syn = 37;//��ʶ���ֱ��룺����<
        }
        ++p;
        return;
    }
    else if(ch == '>')
    {//������> >= >>
        ++p;
        if(project[p] == '=')
        {
            syn = 40;//��ʶ���ֱ��룺����>=
        }
        if(project[p] == '>')
        {
            syn = 59;//��ʶ���ֱ��룺����>>
        }
        else//>
        {
            --p;
            syn = 39;//��ʶ���ֱ��룺����>>
        }
        ++p;
        return;
    }
    else if(ch == '=')
    {//������= ==
        ++p;
        if(project[p] == '=')//==
        {
            syn = 42;
        }
        else
        {//=
            --p;
            syn = 41;
        }
        ++p;
        return;
    }
    else if(ch == '!')
    {//������! !=
        ++p;
        if(project[p] == '=')//==
        {
            syn = 43;
        }
        else
        {
            --p;
            syn = 68;
        }
        ++p;
        return;
    }
    else if(ch == '&')
    {//������& &&
        ++p;
        if(project[p] == '&')//&&
        {
            syn = 53;
        }
        else
        {//&
            --p;
            syn = 52; 
        }
        ++p;
        return;
    }
    else if(ch == '|')
    {//������| ||
        ++p;
        if(project[p] == '|')//||
        {
            syn = 55;
        }
        else
        {
            --p;
            syn = 54;
        }
        ++p;
        return;
    }
    else if(ch == '\0')//�ļ�����
    {
        syn = 0;
    }
    else
    {
        cout<<"����:"<<ch<<endl;
        exit(0);
    }
}

int main()
{
    ifstream infile; 
    infile.open("main.my"); 

    int p=0;
    char project[10000];    //���򻺴�
    while (!infile.eof())
    {
        infile.get(project[p++]);
    }
    project[p++] = '\0';
    infile.close();

    cout << "Դ����Ϊ:\n" << "_______________________________________________________________\n\n" 
        << project << endl
        << "\n_______________________________________________________________\n\n";
    filter(project,p);
    cout << "���˺��Դ����Ϊ:\n" << "_______________________________________________________________\n\n" 
        << project << endl
        << "\n_______________________________________________________________\n";

    p=0;
    int syn = -1;
    char token[MAX_TEMP] = {0};
    while(syn != 0)//��ʼɨ��
    {
        scanner(syn,project,token,p);
        if(syn == 100)//��ʶ��
        {
            for(int i = 0;i<1000;i++)
            {//�����ʶ����
                if(strcmp(idtable[i].text,token) == 0)
                {//�Ѵ��ڱ���
                    break;
                }
                else if(strcmp(idtable[i].text,"") == 0)
                {
                    strcpy(idtable[i].text,token);
                    break;
                }
            }
            cout<<"��ʶ��:\t"<<token<<endl;
            // out<<"��ʶ��:"<<token<<endl;
        }
        else if(syn == 99 || syn == 101)//����
        {
            cout<<"����:\t"<<token<<endl;
            // out<<"����:"<<token<<endl;
        }
        else if(syn <= 32 && syn >= 1)//������
        {
            cout << "�ؼ���:\t" << reserveWord[syn - 1] << endl;
            // out<<reserveWord[syn - 1]<<":"<<syn<<endl;
        }
        else if(syn >= 33 && syn <= 68)//���������
        {
            cout << "�����:\t" << operatorOrDelimiter[syn - 33] << endl;
            // out<<operatorOrDelimiter[syn - 33]<<":"<<syn<<endl;
        }
    
    }

    return 0;
}
