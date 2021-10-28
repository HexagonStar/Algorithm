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
    void invert(SNode *next)
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
    void converse(int system, int num)
    {
        int tmp = 0;
        while (num)
        {
            tmp = num % system;
            this->push(tmp);
            num /= system;
        }
    }
    void print()
    {
        SNode *p = top;
        while (p)
        {
            cout << p->val;
            p = p->next;
        }
    }
};
int main()
{
    //只模拟10以下的进制转换。
    int newSystem = 0, originNum = 0;
    cin >> newSystem >> originNum;
    Stack conversedNum;
    conversedNum.converse(newSystem, originNum);
    conversedNum.print();
}