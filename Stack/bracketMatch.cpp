#include <iostream>
#include <string>
using namespace std;
class SNode
{
public:
    char val;
    SNode *next;
    SNode()
    {
        val = '?';
        next = nullptr;
    }
    SNode(char val)
    {
        this->val = val;
        next = nullptr;
    }
    void invert(char val)
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
    void push(char val)
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
    bool empty()
    {
        if (bottom == top)
            return true;
        else
            return false;
    }
    void clear()
    {
        while (!(bottom == top))
        {
            this->pop();
        }
    }
    void validBracket(string sample)
    {
        char a;
        for (int i = 0; i < sample.length(); i++)
        {
            a = sample[i];
            if (a == '(' || a == '[' || a == '{')
            {
                this->push(a);
            }
            else
            {
                switch (a)
                {
                case ')':
                    if (this->Top()&&this->Top()->val == '(')
                        this->pop();
                    else
                    {
                        cout << "invalid" << endl;
                        return;
                    }
                    break;
                case ']':
                    if (this->Top()&&this->Top()->val == '[')
                        this->pop();
                    else
                    {
                        cout << "invalid" << endl;
                        return;
                    }
                    break;
                case '}':
                    if (this->Top()&&this->Top()->val == '{')
                        this->pop();
                    else
                    {
                        cout << "invalid" << endl;
                        return;
                    }
                    break;
                }
            }
        }
        if (this->empty())
            cout << "valid" << endl;
        else
            cout << "invalid" << endl;
    }
};
int main()
{
    int n;
    Stack Bracket;
    string sample;
    cin >> n;
    while (n--)
    {
        cin >> sample;
        Bracket.validBracket(sample);
        Bracket.clear();
    }
}