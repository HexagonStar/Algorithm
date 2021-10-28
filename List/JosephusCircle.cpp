#include <iostream>
using namespace std;
class Node
{
public:
    Node *succ = nullptr;
//数据域：每个人的密码，最一开始的位置
    int val;
    int index;
    void insert(int val)
    {
        Node *next = new Node(val);
        next->index = this->index + 1;
        this->succ = next;
    };
    void insert(Node *next)
    {
        this->succ = next;
    }
    Node()
    {
        val = 0;
        index = 0;
    }
    Node(int val)
    {
        this->val = val;
    }
};
class LinkedList//和上一题模板差不多，区别在插入时始终让尾结点指向第一位
{
public:
    int size = 0;
    Node *head;
    Node *tail;
    void print()
    {
        int _size = size;
        if (!size)
            cout << "empty" << endl;
        else
        {
            tail = head;
            tail = tail->succ;
            while (_size--)
            {
                cout << tail->val << " " << tail->index << " ";
                tail = tail->succ;
            }
            cout << endl;
        }
    }
    LinkedList()
    {
        Node *newhead = new Node();
        head = newhead;
        tail = head;
    }
    void insert(int val)
    {
        size++;
        tail->insert(val);
        tail = tail->succ;
        tail->succ = head->succ;//尾结点的后继改为头节点的后继(即第一位)
    }
    Node *nodeAt(int posi)
    {
        Node *target = head;
        while (posi--)
        {
            target = target->succ;
        }
        return target;
    }
    void remove(Node *removed)
    {
        int _size = size;
        Node *pre = removed;
        while (--_size)//将pre定位至删除结点的前驱
        {
            pre = pre->succ;
        }
        pre->succ = removed->succ;//修改指针域
        removed->succ = nullptr;
        delete removed;
        size--;//更新规模
    }
    void numberOff(int password)
    {
        Node *beginNode = head;
        beginNode = beginNode->succ;
        while (size)
        {
            while (--password)//模拟报数
            {

                beginNode = beginNode->succ;
            }
            password = beginNode->val;//记录新密码
            cout << beginNode->index << " ";//打印删除节点
            Node *removed = beginNode;
            beginNode = beginNode->succ;
            remove(removed);
        }
    }
};
int main()
{
    LinkedList Joesphus;
    int password, num, pw;
    cin >> password >> num;
    while (num--)
    {
        cin >> pw;
        Joesphus.insert(pw);
    }
    Joesphus.numberOff(password);
}