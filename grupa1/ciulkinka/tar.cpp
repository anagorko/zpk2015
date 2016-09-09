#include<iostream>
#include<math.h>

using namespace std;

int rozwiaz(long long int p_, long long q_)
{
    long long int pocz = 0;
    long long int kon = 9223372036854775807; // tyle moze max miec long long int
    long long int sr;

    while (pocz < kon)
    {
        sr = (pocz + kon) / 2;
        if (pow(sr, 3) + (p_ * sr) >= q_)
            kon = sr;
        else
            pocz = sr + 1;
    }
    return pocz;
}

int main()
{
    long long int n; //liczba czastek
    cin >> n;

    long long int p[n];
    long long int q[n];

    for (long long int i = 0; i < n; i++)
    {
        cin >> p[i] >> q[i];
    }

    /*
    postac i-tego rownania:
    x^3 + (p[i] * x) = q[i]
    */

    int x;
    for (int i = 0; i < n; i++)
    {
        x = rozwiaz(p[i], q[i]);
        if (pow(x, 3) + (p[i] * x) != q[i])
        {
            cout << "NIE" << endl;
        } else
        {
            cout << x << endl;
        }
    }
}
