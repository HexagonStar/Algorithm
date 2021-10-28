#include <iostream>
#define DEFAULTNUM 2
using namespace std;
//双向栈+队列
enum Kind
{
    carMini,
    car,
    carPro,
};
class Car
{
public:
    char mark;
    int time;
    Kind kind;
    Car()
    {
        mark = '?';
        time = 0;
        kind = car;
    }
    Car(char mark, int time, int k)
    {
        this->mark = mark;
        this->time = time;
        switch (k)
        {
        case 0:
            this->kind = carMini;
            break;
        case 1:
            this->kind = car;
            break;
        case 2:
            this->kind = carPro;
            break;
        }
    }
    void print(Car car)
    {
        switch (car.kind)
        {
        case carMini:
            cout << "carMini " << this->mark << " comes at " << car.time << " and leaves at " << this->time << " , totally costs " << 1 * (this->time - car.time) << " $" << endl;
            break;
        case Kind::car:
            cout << "car " << this->mark << " comes at " << car.time << " and leaves at " << this->time << " , totally costs " << 2 * (this->time - car.time) << " $" << endl;
            break;
        case carPro:
            cout << "carPro " << this->mark << " comes at " << car.time << " and leaves at " << this->time << " , totally costs " << 3 * (this->time - car.time) << " $" << endl;
            break;
        }
    };
};
class carNode
{
public:
    Car car;
    carNode *next;
    carNode()
    {
        car = Car{};
        next = nullptr;
    }
    carNode(Car car)
    {
        this->car = car;
        next = nullptr;
    }
    void insert(Car next)
    {
        carNode *tmp = new carNode(next);
        this->next = tmp;
    }
    void insert(carNode *next)
    {
        this->next = next;
    }
};
class doubleStack
{
public:
    carNode *park;

    int ltop, lbottom, rtop, rbottom;
    int capacity = DEFAULTNUM;
    doubleStack()
    {
        park = new carNode[2 * DEFAULTNUM];
        lbottom = 0;
        ltop = 0;
        rbottom = 2 * DEFAULTNUM - 1;
        rtop = 2 * DEFAULTNUM - 1;
    }
    doubleStack(int num)
    {
        capacity = num;
        park = new carNode[2 * num];
        lbottom = 0;
        ltop = 0;
        rbottom = 2 * num - 1;
        rtop = 2 * num - 1;
    }
    void lpush(Car car)
    { //isFull=false
        park[ltop++] = carNode(car);
    };
    void rpush(Car car)
    {
        park[rtop--] = carNode(car);
    };
    carNode lpop()
    {
        carNode tmp = park[ltop];
        ltop--;
        return tmp;
    };
    carNode rpop()
    {
        carNode tmp = park[rtop];
        rtop++;
        return tmp;
    };
    void leave(Car car)
    {
        int index = 0;
        for (int i = 0; i < ltop; i++)
        {
            if (park[i].car.mark == car.mark)
            {
                index = i; //标记要走的车
            }
        }
        int e1 = ltop - index;
        int e2 = e1;
        while (e1--)
        {
            carNode tmp = lpop();
            rpush(tmp.car);
        }
        Car carOrigin = lpop().car;
        car.print(carOrigin);
        while (e2--)
        {
            carNode tmp = rpop();
            lpush(tmp.car);
        }
    };
    bool isFull()
    {
        if (ltop == capacity)
            return true;
        else
            return false;
    };
};
class Queue
{
public:
    carNode *front, *rear;
    Queue()
    {
        front = rear = new carNode();
    }
    void enQueue(Car car)
    {
        carNode *e = new carNode{car};
        carNode *iter = front;
        while (iter->next)
        {
            iter = iter->next;
        }
        iter->next = e;
    };
    Car deQueue()
    {
        Car e = front->next->car;
        carNode *tmp = front->next;
        if (front->next->next)
        {
            front->next = front->next->next;
            delete tmp;
        }
        else
        {
            front->next = nullptr;
            delete tmp;
        }
        return e;
    };
    bool isEmpty()
    {
        if (front->next)
            return false;
        else
            return true;
    };
};
class ParkandRoad
{
public:
    doubleStack *Park;
    Queue *Road;
    ParkandRoad()
    {
        Park = new doubleStack();
        Road = new Queue();
    }
    ParkandRoad(int num)
    {
        Park = new doubleStack(num);
        Road = new Queue();
    }
    void Arrive(Car car)
    {
        if (Park->isFull())
        {
            Road->enQueue(car);
        }
        else
        {
            Park->lpush(car);
        }
    };
    void Leave(Car car)
    {
        Park->leave(car); //空出车位给road上的
        if (!Road->isEmpty())
        {
            Car e = Road->deQueue();
            e.time = car.time;
            Park->lpush(e);
        }
    };
};
int main()
{
    int num, time, kind;
    char status, mark;

    cin >> num;
    ParkandRoad parkArrange{num};
    cin >> status >> mark >> time >> kind;
    while (status != 'E')
    {
        switch (status)
        {
        case 'A':
            parkArrange.Arrive(Car{mark, time, kind});
            break;
        case 'D':
            parkArrange.Leave(Car{mark, time, kind});
            break;
        }
        cin >> status >> mark >> time >> kind;
    }
}