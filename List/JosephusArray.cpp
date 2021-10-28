#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Josephus
{
public:
//默认后继为-1
    int val = 0;
    int nextIndex = -1;
    Josephus(){};
    Josephus(int val)
    {
        this->val = val;
    }
};
int num, password, pw, size = 0;
Josephus *JosephusArray[100] = {nullptr};
void offNumber(int);
void erase(int);
int main()
{
    cin >> password >> num;
    size = num;
//手动插入头结点
    JosephusArray[0] = new Josephus(0);
    JosephusArray[0]->nextIndex = 1;
    for (int i = 0; i < num; i++)
    {
        cin >> pw;
        //从1开始存储数据
        JosephusArray[i + 1] = new Josephus(pw);
        if (i)//更新上一位的后继，
            JosephusArray[i]->nextIndex = i + 1;
    }
    //将末尾的后继设为头结点的后继，达成循环
    JosephusArray[num]->nextIndex = JosephusArray[0]->nextIndex;
    //开始报数
    offNumber(password);
}
void offNumber(int password)
{
    int index = JosephusArray[0]->nextIndex;
    int num_ = num, nextindex = index;
    while (num_--)//一共num人，报num次数
    {
        while (--password)//模拟报数，找到出列的人
        {
            nextindex = JosephusArray[nextindex]->nextIndex;
        }
        index = nextindex;//存储出列人下标
        password = JosephusArray[index]->val;//更新密码
        cout << index << " ";//打印出列的人
        nextindex = JosephusArray[index]->nextIndex;//先保存下一位报数的人，再删除
        erase(index);
    }
}
void erase(int index)
{
    int targetIndexpre = index;
    int size_ = size;
    while (--size_)//根据规模找到删除结点的前驱
    {
        targetIndexpre = JosephusArray[targetIndexpre]->nextIndex;
    }
    //修改“指针”域
    JosephusArray[targetIndexpre]->nextIndex=JosephusArray[index]->nextIndex;
    delete JosephusArray[index];
    size--;//更新规模
    return;
}
