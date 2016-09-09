#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{
    int n;
    cin >> n;
    int tab[n];
    for (int i = 0; i < n; ++i)
        cin >> tab[i];
    int odleglosc_tymcz = 0, odleglosc_max = 0;
    if (tab[n - 1]!= tab[0])
        cout << n - 1 << endl;
    else
    {
        for (int i = 1; i < n - 1; ++i)
        {
            if (tab[i]!=tab[0])
            {
                odleglosc_tymcz = max(i, n - i - 1);
                odleglosc_max = max(odleglosc_tymcz, odleglosc_max);
            }
        }
        if (odleglosc_max == 0)
        cout << "BRAK" << endl;
        else 
            cout << odleglosc_max << endl;
        
    }
}
