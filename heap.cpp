#include <iostream>
#include <vector>
using namespace std;

//堆化
//传入数组和下标k，k的左右子树都满最大堆性质，函数讲myheap整体调整为最大堆
void adjustHeap(vector<int> &myheap, int k,int size)
{
    //只要索引不超过数组长度，就不断向下调整
    while (k<size)
    {
        int left = 2*k+1;   //左节点下标
        int right = 2*k+2;  //右节点下标
        int maxium = k;     //备份当前节点

        //有左子节点，且当前节点小于左子节点
        if(left<size && myheap[maxium]<myheap[left])
            maxium = left;
        //有右子节点，且当前节点小于右子节点
        if(right<size && myheap[maxium]<myheap[right])
            maxium = right;
        //当前节点比左右子节点都要大，不需要调整了
        if(maxium==k)
            break;
        //把当前的顺序进行调整
        swap(myheap[k],myheap[maxium]);
        k = maxium;
    }  
}
/*
    从最后一个父节点(size/2-1的位置)逐个往前调整所有父节点（直到根节点）
    确保每一个父节点都是一个最大堆，最后整体形成一个最大堆 
*/
void heap_bulid(vector<int> &myheap)
{
    for(int i=(myheap.size()/2-1); i >= 0; i--)
        adjustHeap(myheap, i,myheap.size());  //堆化
}
//堆排序
void heap_sort(vector<int> &myheap)
{
    int size = myheap.size();
    for(int i=size-1;i>=0;i--)
    {
        //把根节点与最后节点交互，大数就排到最后   
        swap(myheap[0],myheap[i]);  
        //把前面9个原始中，0索引元素做一下调整
        adjustHeap(myheap,0,i);
    }
}

int main()
{
    //vector<int> myheap{90,7,6,40,70,60,80,3,0,2,1,4};
    char a[] = {90,7,6,40,70,60,80,3,0,2,1,4};
    vector<int> myheap;
    for(int i=0;i<12;i++)
        myheap.push_back(a[i]);

    heap_bulid(myheap);
    heap_sort(myheap);

    for(int i=0;i<myheap.size();i++)
        cout << myheap[i] << ", ";

    return 0;
}

/*
    1.堆树是一颗完全二叉树；
    2.堆树中某个节点的值总是不大于或不小于其孩子节点的值；
    3.堆树中每个节点的子树都是堆树。

    数组实现堆
        父节点：(i-1)/2
        左孩子：2i+1
        右孩子：2i+2
*/