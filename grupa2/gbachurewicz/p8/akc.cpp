#include <iostream>

using namespace std;


bool szukaj (int x, int *t, int p, int k)
{
    int first, last, key, mid, ile;
    ile = 0;
    first = p;
    last = k;
    key = x;
    bool found = false;
while (first <= last && !found){

        mid = (first + last)/2;

        if (key > t[mid])
            first = mid + 1;
        else if (key < t[mid])
            last = mid -1;
        else {
            found = true;
            return found;
        }
    }

    if (!found)
        return false;

}

int main()
{
    int n, ile, licznik;
    licznik = 0;
    cin >> n; //liczba czastek
    int t[n];
    for (int i=0; i< n;i++){
        cin >> t[i];
    }

    cin >> ile; //liczba szukanych predkosci
    int szukane[ile]; //tablica szukanych predkosci
    for (int i=0; i< ile;i++){
        cin >> szukane[i];
    }

    for (int i=0; i< ile;i++){
        if (szukaj(szukane[i], t, 0, n-1))
        {
            licznik++;
            // tutaj powinno sie usunac znaleziony element i jeszcze raz zaczac szukac element szukane[i]
        }
    cout << licznik << endl;
    licznik = 0;

    }
}
