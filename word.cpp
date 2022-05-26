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


//保留字表
static char reserveWord[32][MAX_TEMP] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
//界符运算符
static char operatorOrDelimiter[36][10] = {
   "+","-","*","/","<","<=",">",">=","=","==",
   "!=",";","(",")","^",",","\"","\'","#","&",
   "&&","|","||","%","~","<<",">>","[","]","{",
   "}","\\",".","\?",":","!"
};

//标识符表
// static  char IDentifierTbl[1000][50] = {""};

static word idtable[1000];

//判断是否为数字
bool isDigit(char ch)
{
    if(ch>= '0' && ch <= '9')
        return true;
    return false;
}

//判断是否为字母或下划线
bool isLetter(char ch)
{
    if((ch>= 'a' && ch<='z') || ( ch <= 'Z' && ch >= 'A')|| ch == '_')
        return true;
    return false;
}

//判断是否为保留字
int isReserve(char *s)
{   
    for(int i=0;i<32;++i)
    {
        if(strcmp(reserveWord[i],s) == 0)
            return i+1;//返回种别码
    }
    return -1;    
}
//源程序预处理，过滤注释和换行回车制表符
void filter(char *s,int len)
{
    char tmp[10000];
    int p = 0;
    for(int i=0;i<len;++i)
    {
        if(s[i] == '/' && s[i+1] == '/')//单行注释
        {
            while(s[i++]!='\n')i;//扫描到换行符为止
        }
        if(s[i] == '/' && s[i+1] == '*')//多行注释
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
        }//去掉空余符
        if(s[i] != '\n' && s[i] != '\t' && s[i] != '\v' && s[i] != '\r')
        {
            tmp[p++] = s[i];
        }
        // 多个空格合为一个
        // if(s[i] == ' ')
        // {
        //     while (s[i]==' ') ++i;
        //     tmp[p++] = ' ';     
        // }
    }
    tmp[p] = '\0';
    strcpy(s,tmp);
}

//扫描源程序，syn是种别码，token是当前扫描的单词，p为扫描位置索引
void scanner(int &syn,char * project,char * token,int &p)
{   
    int count = 0;
    char ch;
    ch = project[p];
    while(ch == ' ')//去掉空格
    {
        ++p;
        ch = project[p];
    }
    for(int i=0;i<MAX_TEMP;i++)//清空token
    {
        token[i] = '\0';
    }
    //以字母开头
    if(isLetter(project[p]))
    {
        token[count++] = project[p++];
        while(isLetter(project[p])||isDigit(project[p]))//后面是字母或数字
        {
            token[count++] = project[p++];
        }
        token[count] = '\0';
        syn = isReserve(token);//标识符种别码：关键字（1~32）
        if(syn == -1)
        {//若不是保留字则是标识符
            syn = 100;//标识符种别码：非保留关键字
        }
        return;
    }
    //以数字开头
    else if(isDigit(project[p]))
    {
       token[count++] = project[p++]; 
       while(isDigit(project[p]))//后面是数字
        {
            token[count++] = project[p++];
        }
        token[count] = '\0';
        syn = 99;//标识符种别码：数字常数
        return;
    }
    //字符
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
                syn = 33+i;//标识符种别码：符号（33~68）
                break;
            }
        }
        return;
    }
    //字符串常数
    else if(ch == '\"')
    {
        token[count++] = project[p++];
        char c;
        while(!(project[p]=='\"' && project[p-1]!='\\'))//到双引号结尾
        {
            c = project[p];
            token[count++] = project[p++];
        }
        token[count++] = project[p++];
        token[count] = '\0';
        syn = 101;  //标识符种别码：字符串常数
        return;
    }
    else if(ch == '<')
    {//可能是< <= <<
        ++p;
        if(project[p] == '=')//<=
        {
            syn = 38;//标识符种别码：符号<=
        }
        if(project[p] == '<')//<<
        {
            syn = 58;//标识符种别码：符号<<
        }
        else//<
        {
            --p;
            syn = 37;//标识符种别码：符号<
        }
        ++p;
        return;
    }
    else if(ch == '>')
    {//可能是> >= >>
        ++p;
        if(project[p] == '=')
        {
            syn = 40;//标识符种别码：符号>=
        }
        if(project[p] == '>')
        {
            syn = 59;//标识符种别码：符号>>
        }
        else//>
        {
            --p;
            syn = 39;//标识符种别码：符号>>
        }
        ++p;
        return;
    }
    else if(ch == '=')
    {//可能是= ==
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
    {//可能是! !=
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
    {//可能是& &&
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
    {//可能是| ||
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
    else if(ch == '\0')//文件结束
    {
        syn = 0;
    }
    else
    {
        cout<<"错误:"<<ch<<endl;
        exit(0);
    }
}

int main()
{
    ifstream infile; 
    infile.open("main.my"); 

    int p=0;
    char project[10000];    //程序缓存
    while (!infile.eof())
    {
        infile.get(project[p++]);
    }
    project[p++] = '\0';
    infile.close();

    cout << "源程序为:\n" << "_______________________________________________________________\n\n" 
        << project << endl
        << "\n_______________________________________________________________\n\n";
    filter(project,p);
    cout << "过滤后的源程序为:\n" << "_______________________________________________________________\n\n" 
        << project << endl
        << "\n_______________________________________________________________\n";

    p=0;
    int syn = -1;
    char token[MAX_TEMP] = {0};
    while(syn != 0)//开始扫描
    {
        scanner(syn,project,token,p);
        if(syn == 100)//标识符
        {
            for(int i = 0;i<1000;i++)
            {//插入标识符表
                if(strcmp(idtable[i].text,token) == 0)
                {//已存在表中
                    break;
                }
                else if(strcmp(idtable[i].text,"") == 0)
                {
                    strcpy(idtable[i].text,token);
                    break;
                }
            }
            cout<<"标识符:\t"<<token<<endl;
            // out<<"标识符:"<<token<<endl;
        }
        else if(syn == 99 || syn == 101)//常数
        {
            cout<<"常数:\t"<<token<<endl;
            // out<<"常数:"<<token<<endl;
        }
        else if(syn <= 32 && syn >= 1)//保留字
        {
            cout << "关键字:\t" << reserveWord[syn - 1] << endl;
            // out<<reserveWord[syn - 1]<<":"<<syn<<endl;
        }
        else if(syn >= 33 && syn <= 68)//运算符或界符
        {
            cout << "运算符:\t" << operatorOrDelimiter[syn - 33] << endl;
            // out<<operatorOrDelimiter[syn - 33]<<":"<<syn<<endl;
        }
    
    }

    return 0;
}
