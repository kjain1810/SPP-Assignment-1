#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    int n = 5;
    cout << n << "\n";
    int x[5], y[5];
    x[0] = gen() % 400 + 601;
    y[0] = gen() % 400 + 601;
    for (int a = 1; a < 5; a++)
    {
        x[a] = y[a - 1];
        y[a] = gen() % 400 + 601;
    }
    for (int a = 0; a < 5; a++)
    {
        cout << x[a] << " " << y[a] << "\n";
        for (int i = 0; i < x[a]; i++)
        {
            for (int j = 0; j < y[a]; j++)
            {
                int here = gen();
                here %= 11;
                cout << here << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}