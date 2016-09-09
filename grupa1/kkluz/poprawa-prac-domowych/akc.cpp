#include <iostream>
using namespace std;

int n;
int licznik = 0;

//korzystając z wyszukiwania binarnego znajduje pierwsze oraz ostanie wystąpienie szukanej predkosci
int pozycja_pierwsza(int s[], int b, int a, int k)
{
    while (a > b)
    {
        int srodek = (a + b)/2;
        if (s[srodek] == k)
            {
            if (licznik == 0)
            {
                licznik = srodek;
            }
        }
        if (s[srodek] < k)
        {
            b = srodek + 1;
        } else{
            a = srodek;
        }
    }
    if (s[a] == k)
    {
       return a;
    }
    else
    {
        return -1;
    }
}


int pozycja_ostatnia(int s[], int b, int a, int k){
    while (a > b){
        int srodek = (a + b + 1) / 2;
        if (s[srodek] <= k)
        {
            b = srodek;
        }
        else
        {
            a = srodek - 1;
        }
    }
    if (s[b] == k)
    {
        return b;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int t[n],q;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
    }
    cin >> q;
    int a[q];
    for (int i = 0; i < q; i++){
        licznik = 0;
        cin >> a[i];
        int pierwsza = pozycja_pierwsza(t, 0, n - 1, t[i]);
        int ostatnia = pozycja_ostatnia(t, licznik, n - 1, t[i]);
        if (pierwsza == -1 ||
            ostatnia == -1){
            cout << 0 << endl;
        }
        else
        {
            cout << 1 + ostatnia - pierwsza << endl;
        }
    }
}
