#include <iostream>

using namespace std;

int iloscLiczb(int tab[], int p, int k, int q)
{
    int poc, kon, sro, poczatek, koniec;
    poc = p;
    kon = k;
    while (poc < kon)
    {
        sro = (poc + kon) / 2;
        if (tab[sro] >= q)
            kon = sro;
        else
            poc = sro + 1;
    }
    if (tab[poc] == q)
        poczatek = poc;
    else
        return 0;

    poc = p;
    kon = k;
    while (poc < kon)
    {
        sro = (poc + kon+1) / 2;
        if (tab[sro] <= q)
            poc = sro;
        else
            kon = sro + 1;
    }
        koniec = poc;
    return koniec - poczatek + 1;


}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, q, p;
    int *tab;

    cin >> n;
    tab = new int [n];
    for (int i = 0; i < n; i++)
        cin >> tab[i];

    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> p;
        cout << iloscLiczb (tab, 0, n-1 , p);
    }

    return 0;
}
