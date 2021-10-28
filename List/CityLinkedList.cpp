#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class coord //城市的位置坐标
{
public:
    int x;
    int y;
    coord()
    {
        x = 0;
        y = 0;
    }
    coord(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    double distanceWith(coord target) //与target的距离
    {
        return sqrt((this->x - target.x) * (this->x - target.x) + (this->y - target.y) * (this->y - target.y));
    }
    friend ostream &operator<<(ostream &out, coord s) //重载<<，方便输出
    {
        out << "(" << s.x << "," << s.y << ")";
        return out;
    }
};
class Node //为简略代码，数据域均设为public
{
public:
    //数据域：后继、位置、城市名
    Node *succ = nullptr;
    coord position;
    string name;
    //构造函数
    Node()
    {
        position.x = 0;
        position.y = 0;
        name = "";
    }
    Node(coord posi, string name)
    {
        position.x = posi.x;
        position.y = posi.y;
        this->name = name;
    }
    //两种插入方式
    void insert(coord posi, string name)
    {
        Node *next = new Node(posi, name);
        this->succ = next;
    };
    void insert(Node *next)
    {
        this->succ = next;
    }
};
class LinkedList
{
public:
    //数据域：链表长度、头结点、尾结点
    int size = 0;
    Node *head;
    Node *tail;
    //构造函数
    LinkedList()
    {
        Node *newhead = new Node();
        head = newhead;
        tail = head;
    }
    //两种插入方式
    void insert(coord posi, string name)
    {
        size++;
        tail->insert(posi, name);
        tail = tail->succ;
    }
    void insert(Node *next)
    {
        size++;
        tail->insert(next);
        tail = tail->succ;
    }
    void print() //打印所有城市信息，若为空表则打印empty
    {
        cout << "Test function print:" << endl;
        if (!size)
            cout << "empty" << endl;
        else
        {
            tail = head;
            tail = tail->succ;
            while (tail)
            {
                cout << "City " << tail->name << " in " << tail->position << endl;
                tail = tail->succ;
            }
            cout << endl;
        }
    }
    Node *nodeAt(int posi) //返回第posi个城市，若超出范围则抛出异常
    {
        Node *target = head;
        while (posi--)
        {
            if (target->succ == nullptr)
                throw -1;
            target = target->succ;
        }
        return target;
    }

    void remove(string targetName) //删除目标结点，若不在链表中，抛出异常
    {
        cout << "Test function remove:" << endl;
        Node *removed = head;
        Node *pre = head;
        removed = removed->succ;
        while (removed)
        {
            if (removed->name == targetName)
            {
                pre->succ = removed->succ;
                removed->succ = nullptr;
                size--;
                tail = nodeAt(size);
                delete removed;
                cout << "Successfully deleted" << endl;
                return;
            }
            else
            {
                removed = removed->succ;
                pre = pre->succ;
            }
        }
        throw -1;
    }
    coord getPosi(string targetName) //返回目标结点的坐标
    {
        cout << "Test function getPosi:" << endl;
        Node *target = head;
        target = target->succ;
        while (target)
        {
            if (target->name == targetName)
                return target->position;
            target = target->succ;
        }
        throw -1;
    }
    void findDistLessThanD(coord position, double dist) //搜索所有与目标位置距离小于dist的城市
    {
        Node *target = head;
        target = target->succ;
        bool flag = 0;
        cout << "Test function findDistLessThanD"
             << "(" << position << "," << dist << "):" << endl;
        while (target)
        {
            if (target->position.distanceWith(position) < dist)
            {
                cout << "City " << target->name << " in" << target->position << " satisifies the condition" << endl;
                flag = 1;
            }
            target = target->succ;
        }
        if (!flag)
            cout << "Not Found" << endl;
    }
    void update(string targetName, coord newposi) //更新目标结点的坐标
    {
        cout << "Test function update:" << endl;
        Node *target = head;
        target = target->succ;
        while (target)
        {
            if (target->name == targetName)
            {
                target->position = newposi;
                cout << "City " << target->name << " is in " << target->position << " now" << endl;
                return;
            }
            target = target->succ;
        }
        throw -1;
    }
};
int main()
{
    LinkedList City;
    for (int i = 0; i < 30; i++) //随机生成30个城市，以字典序命名
    {
        int k = i;
        string name = "";
        do
        {
            name += 'A' + k % 26;
            k /= 26;
        } while (k);
        City.insert(coord(rand() % 100 + 1, rand() % 100 + 1), name);
    }

    City.print();
    try //测试nodeAt（越界情况）
    {
        City.nodeAt(100);
    }
    catch (int &e)
    {
        cout << "OUT OF INDEX" << endl;
    }
    try //测试getPosi
    {
        cout << City.getPosi("AB") << endl;
    }
    catch (int &e)
    {
        cout << "NOT FOUND" << endl;
    }

    City.findDistLessThanD(coord(0, 0), 50); //测试findDistLessThanD

    try //测试remove（未命中情况）
    {
        City.remove("Cdd");
    }
    catch (int &e)
    {
        cout << "NOT FOUND" << endl;
    }

    try //测试remove（命中情况）
    {
        City.remove("C");
    }
    catch (int &e)
    {
        cout << "NOT FOUND" << endl;
    }

    try //测试update
    {
        City.update("I", coord(11, 11));
    }
    catch (int &e)
    {
        cout << "NOT FOUND" << endl;
    }

    City.print();
}
