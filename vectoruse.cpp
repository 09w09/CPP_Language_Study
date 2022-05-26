#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
using namespace std;

//����ͨ�����ķ�ʽʵ���Զ����������
bool mycomp(int i, int j) {
    return (i < j);
}
//�Ժ�������ķ�ʽʵ���Զ����������
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

    //���õ�һ���﷨��ʽ���� 32��71��12��45 ��������
    sort(myvector.begin(), myvector.begin() + 4); //(12 32 45 71) 26 80 53 33

    //���õڶ����﷨��ʽ������STL��׼���ṩ�������ȽϹ��򣨱��� greater<T>����������
    sort(myvector.begin(), myvector.begin() + 4, std::greater<int>()); //(71 45 32 12) 26 80 53 33
   
    //���õڶ����﷨��ʽ��ͨ���Զ���ȽϹ����������
    sort(myvector.begin(), myvector.end(), mycomp2());  //12 26 32 33 45 53 71 80

    //��� myvector �����е�Ԫ��
    for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
        cout << *it << ' ';
    }

    return 0;
}