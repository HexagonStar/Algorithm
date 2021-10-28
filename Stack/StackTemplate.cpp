#include <iostream>
using namespace std;
class SNode
{
public:
    int val;
    SNode *next;
    SNode()
    {
        val = -1;
        next = nullptr;
    }
    SNode(int val)
    {
        this->val = val;
        next = nullptr;
    }
    void invert(int val)
    {
        next = new SNode(val);
    }
    void invert(SNode* next)
    {
        this->next = next;
    }
}; 
class Stack
{
public:
    //栈顶栈底
    SNode *top;
    SNode *bottom;
    //初始化
    Stack()
    {

        bottom = new SNode();
        top = bottom;
    }
    //返回栈顶
    SNode *Top()
    {
        if (bottom == top)
            return nullptr;
        else
            return top;
    }
    //弹出栈顶
    void pop()
    {
        if (bottom == top)
            return;
        else if (!top->next)
        {
            SNode *tmp = top;
            top = bottom;
            delete tmp;
        }
        else
        {
            bottom->next = top->next;
            SNode *tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    //推入栈顶
    void push(int val)
    {
        if (bottom == top)
        {
            top->next = new SNode(val);
            top = top->next;
        }
        else
        {
            SNode *newTop = new SNode(val);
            newTop->next = top;
            bottom->next = newTop;
            top = bottom->next;
        }
    }
    void push(SNode *newTop)
    {
        if (bottom == top)
        {
            top->next = newTop;
            top = top->next;
        }
        else
        {
            newTop->next = top;
            bottom->next = newTop;
            top = bottom->next;
        }
    }
    void print()
    {
        SNode *p = top;
        while (p)
        {
            cout << p->val << " ";
            p = p->next;
        }
    }
};
 int main()
{
    Stack L1;
    L1.push(1);
    L1.push(2);
    L1.push(3);
    L1.push(4);
    L1.print();
    L1.pop();
    L1.print();
}