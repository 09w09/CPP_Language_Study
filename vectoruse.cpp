#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
using namespace std;

//以普通函数的方式实现自定义排序规则
bool mycomp(int i, int j) {
    return (i < j);
}
//以函数对象的方式实现自定义排序规则
class mycomp2 {
public:
    bool operator() (int i, int j) {
        return (i < j);
    }
};

int main() {
    //vector<int> myvector{ 32, 71, 12, 45, 26, 80, 53, 33 };
    vector<int> myvector;
    myvector.push_back(32);
    myvector.push_back(71);
    myvector.push_back(12);
    myvector.push_back(45);
    myvector.push_back(26);
    myvector.push_back(80);
    myvector.push_back(53); 
    myvector.push_back(33);

    //调用第一种语法格式，对 32、71、12、45 进行排序
    sort(myvector.begin(), myvector.begin() + 4); //(12 32 45 71) 26 80 53 33

    //调用第二种语法格式，利用STL标准库提供的其它比较规则（比如 greater<T>）进行排序
    sort(myvector.begin(), myvector.begin() + 4, std::greater<int>()); //(71 45 32 12) 26 80 53 33
   
    //调用第二种语法格式，通过自定义比较规则进行排序
    sort(myvector.begin(), myvector.end(), mycomp2());  //12 26 32 33 45 53 71 80

    //输出 myvector 容器中的元素
    for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << ' ';
    }

    return 0;
}