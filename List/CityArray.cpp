#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class City //定义结点
{
public:
    //数据域：与链表相比，多出一个nextIndex，用以存储后继结点的下标
    string name = "";
    int x = 0, y = 0;
    int nextIndex = -1;
    City(){};
    City(string name, int x, int y)
    {
        this->name = name;
        this->x = x;
        this->y = y;
    }
    void print()
    {
        cout << "City " << name << " in "
             << "(" << x << "," << y << "),nextIndex is " << nextIndex << endl;
    }
};
//为方便代码编写，将数组设为全局变量。
int num;
City *CityArray[100] = {nullptr};
//函数声明，由于数组为全局变量，不需要传数组指针进去
int find(string targetName);
void erase(string name);
void insert(string name, int x, int y);
void findDistLessThanD(int x, int y, double dist);
void print();
int main()
{
    num = 10；
//手动插入头节点
    CityArray[0] = new City("head", -1, -1);
    CityArray[0]->nextIndex = 1;
    for (int i = 1; i <= num; i++)
    {
        int k = i - 1;
        string name = "";
        do
        {
            name += 'A' + k % 26;
            k /= 26;
        } while (k);
        CityArray[i] = new City(name, rand() % 100 + 1, rand() % 100 + 1);
        if (i)
            CityArray[i - 1]->nextIndex = i;
    }
    print();
    find("D");  //测试find(命中)
    find("CC"); //测试find(未命中)
    erase("E");//测试erase(命中)
    erase("???");//测试erase(未命中)
    insert("aaa", 10, 10);
    print();
    findDistLessThanD(0, 0, 40);
}
int find(string targetName)
{
    cout << "Test find function:" << endl;
    int j = 0;
    do//一路往后找，直到后继为-1
    {
        if (targetName == CityArray[j]->name)
        {
            cout << "FOUND: ";
            CityArray[j]->print();
            return j;
        }
        j = CityArray[j]->nextIndex;
    } while (j != -1);

    cout << "NOT FOUND" << endl;
    return 0;
}
void erase(string name)
{
    cout << "Test erase function:" << endl;
    int flag = 0;
    do
    {
        if (name == CityArray[flag]->name)
        {
            break;
        }
        flag = CityArray[flag]->nextIndex;
    } while (flag != -1);
//如果flag为-1，即为遍历后仍未命中。
    if (flag == -1)
    {
        cout << "NOT FOUND" << endl;
        return;
    }
    int target = 0, targetpre = 0;
    target = CityArray[0]->nextIndex;
    while (--flag)//找到前驱结点
    {
        target = CityArray[target]->nextIndex;
        targetpre = CityArray[targetpre]->nextIndex;
    }
    CityArray[targetpre]->nextIndex = CityArray[target]->nextIndex;//修改“指针”域
    delete CityArray[target];
    cout << "Successfully erased" << endl;
}
void insert(string name, int x, int y)
{
    cout << "Test insert function:" << endl;
    int index = 0;
    while (CityArray[index])//找到数组中位置最靠前的空位，插入新结点
        index++;
    CityArray[index] = new City(name, x, y);
    int j = 0;
    while (1)
    {
        if (CityArray[j]->nextIndex == -1)
        {
            CityArray[j]->nextIndex = index;
            break;
        }
        j = CityArray[j]->nextIndex;
    }
}
void findDistLessThanD(int x, int y, double dist)
{
    int j = 0;
    cout << "Test findDistLessThanD function:" << endl;
    j = CityArray[j]->nextIndex;
    do
    {
        int dis = sqrt((CityArray[j]->x - x) * (CityArray[j]->x - x) + (CityArray[j]->y - y) * (CityArray[j]->y - y));
        if (dist > dis)
        {
            cout << "City " << CityArray[j]->name << " in (" << CityArray[j]->x << "," << CityArray[j]->y << "), distinction is " << dis << endl;
        }
        j = CityArray[j]->nextIndex;
    } while (j != -1);
}
void print()
{
    int j = 0;
    j = CityArray[j]->nextIndex;
    do
    {
        CityArray[j]->print();
        j = CityArray[j]->nextIndex;
    } while (j != -1);
}