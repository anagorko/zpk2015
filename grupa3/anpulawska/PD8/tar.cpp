#include <iostream>

using namespace std;
long long znajdzX (long long p, long long q)
{
    long long x;
    long long poc = 1;
    long long kon = q;
    while (poc < kon)
    {
        x = (poc+kon)/2;
        if ((x*x*x+x*p) >= q)
            kon = x;
        else
            poc = x+1;
    }
    if((poc*poc*poc+poc*p) == q)
        return poc;
    else
        return 0;
}
int main()
{
    int z;
    long long p, q;
    long long *tab;

    cin >> z;
    tab = new long long [z];
    for (int i = 0; i < z; i++)
    {
        cin >> p >> q;
        tab[i] = znajdzX(p, q);
    }
    for (int i = 0; i < z; i++)
    {
        if (tab[i] == 0)
            cout << "NIE" << endl;
        else
            cout << tab[i] << endl;
    }

    return 0;
}
