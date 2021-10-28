#include <iostream>
#include <stack>
using namespace std;
class Node
{
public:
    Node *succ = nullptr;
    int val;
    void insert(int val)
    {
        Node *next = new Node(val);
        this->succ = next;
    };
    void insert(Node *next)
    {
        this->succ = next;
    }
    Node()
    {
        val = 0;
    }
    Node(int val)
    {
        this->val = val;
    }
};
class LinkedList
{
public:
    int size = 0;
    Node *head;
    Node *tail;
    void print()
    {
        if (!size)
            cout << "empty" << endl;
        else
        {
            tail = head;
            tail = tail->succ;
            while (tail)
            {
                cout << tail->val << " ";
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
    }
    void insert(Node *next)
    {
        size++;
        tail->insert(next);
        tail = tail->succ;
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
    Node *removeAt(int posi)
    {
        Node *removed = head;
        for (int i = 0; i < posi; i++)
        {
            removed = removed->succ;
        }
        Node *pre = nodeAt(posi - 1);
        pre->succ = removed->succ;
        removed->succ = nullptr;
        size--;
        tail = nodeAt(size);
        return removed;
    }
    Node *removeFirst()
    {
        return removeAt(1);
    }
};
void reverse(LinkedList &L)
{
    stack<Node *> S;
    int size = L.size;
    while (size--)
    {
        S.push(L.removeFirst());
    }
    while (!S.empty())
    {
        L.insert(S.top());
        S.pop();
    }
}
void reverseMerge(LinkedList &L1, LinkedList &L2)
{
    LinkedList L3;
    while (L1.size > 0 && L2.size > 0)
    {
        if (L1.head->succ->val <= L2.head->succ->val)
        {
            L3.insert(L1.removeFirst());
        }
        else
        {
            L3.insert(L2.removeFirst());
        }
    }
    if (L1.size == 0)
    {
        L3.tail->succ = L2.head->succ;
        L3.size += L2.size;
        L2.size = 0;
        L2.head->succ = nullptr;
    }
    else
    {
        L3.tail->succ = L1.head->succ;
        L3.size += L1.size;
        L1.size = 0;
        L1.head->succ = nullptr;
    }
    reverse(L3);
    L3.print();
}
void crossMerge(LinkedList &L1, LinkedList &L2)
{
    LinkedList L3;
    bool flag = true;
    while (L1.size > 0 && L2.size > 0)
    {
        if (flag)
        {
            L3.insert(L1.removeFirst());
            flag = !flag;
        }
        else
        {
            L3.insert(L2.removeFirst());
            flag = !flag;
        }
    }
    if (L1.size == 0)
    {
        L3.tail->succ = L2.head->succ;
        L3.size += L2.size;
        L2.size = 0;
        L2.head->succ = nullptr;
    }
    else
    {
        L3.tail->succ = L1.head->succ;
        L3.size += L1.size;
        L1.size = 0;
        L1.head->succ = nullptr;
    }
    L3.print();
}
int main()
{
    int T, val, num_1, num_2;

    cin >> T;
    while (T--)
    {
        LinkedList L1;
        LinkedList L2;
        cin >> num_1 >> num_2;

        while (num_1--)
        {
            cin >> val;
            L1.insert(val);
        }

        while (num_2--)
        {
            cin >> val;
            L2.insert(val);
        }
        crossMerge(L1, L2);
    }

    return 0;
}