#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

class Node{
public:
    Node(string s):val(s){}
    string val;
    Node *left;
    Node *right;
};

Node *initTree()
{
    Node *root = new Node("A");
    root->left = new Node("B");
    root->right = new Node("C");

    //B
    root->left->left = new Node("D");
    root->left->right = new Node("E");

    //C
    root->right->left = new Node("F");
    root->right->right = new Node("G");

    //F
    root->right->left->left = NULL;
    root->right->left->right = new Node("H");

    //D
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    //E
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    //H
    root->right->left->right->left = NULL;
    root->right->left->right->right = NULL;
    //G
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    return root;
}
//前序
void preOrderTraverse(Node *p)
{
    if(p==NULL)
        return;

    cout << p->val;
    preOrderTraverse(p->left);
    preOrderTraverse(p->right);
}
//中序
void inOrderTraverse(Node *p)
{
    if(p==NULL)
        return;
 
    inOrderTraverse(p->left);
    cout << p->val;
    inOrderTraverse(p->right);
}
//后序
void postOrderTraverse(Node *p)
{
    if(p==NULL)
        return;
  
    postOrderTraverse(p->left);
    postOrderTraverse(p->right);
    cout << p->val;
}
//层搜索,从上往下
void levelTraverse(Node *p)
{
    queue<Node *> q;
    q.push(p);
    while(!q.empty())
    {
        Node *temp = q.front();q.pop();

        cout << temp->val;
        if(temp->left!=NULL)
            q.push(temp->left);
        if(temp->right!=NULL)
            q.push(temp->right);
    }
}
//前序遍历的非递归版
void depthTraverse(Node *p)
{
    stack<Node *> s;
    s.push(p);
    while (!s.empty())
    {
        Node *temp = s.top();s.pop();

        cout << temp->val;
        if(temp->right!=NULL)
            s.push(temp->right);      
        if(temp->left!=NULL)
            s.push(temp->left);
    }
    
}

int main()
{
    Node *root = initTree();
    preOrderTraverse(root);cout<<endl;
    inOrderTraverse(root);cout<<endl;
    postOrderTraverse(root);cout<<endl;
    levelTraverse(root);cout<<endl;
    depthTraverse(root);cout<<endl;

    return 0;
}


/*
    四种主要的遍历思想为：
        前序遍历：根结点 ---> 左子树 ---> 右子树
        中序遍历：左子树---> 根结点 ---> 右子树
        后序遍历：左子树 ---> 右子树 ---> 根结点
        层次遍历：只需按层次遍历即可
*/