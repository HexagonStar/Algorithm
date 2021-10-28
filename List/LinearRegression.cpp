#include <iostream>
using namespace std;
double kJ(double, double);
double bJ(double, double);
int test[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int main()
{
  int i = 0;
  double k = 0, b = 0, l = 0.001;
  while (1)
  {
    double newk = k - l * kJ(k, b);
    double newb = b - l * bJ(b, k);

    if (newk == k && newb == b)
    {
      break;
    }
    k = newk;
    b = newb;
    i++;
    if (i<400&&i%2)
      cout << "y=" << k << "x+(" << b << ")" << endl;
  }
}
double kJ(double k, double b)
{
  double sum = 0;
  for (int i = 1; i <= 8; i++)
  {
    sum += 2 * i * i * k - 2 * i * test[i - 1] + 2 * i * b;
  }
  return sum / 16;
}
double bJ(double b, double k)
{
  double sum = 0;
  for (int i = 1; i <= 8; i++)
  {
    sum += 2 * b - 2 * test[i - 1] + 2 * k * i;
  }
  return sum / 8;
}