#include <iostream>

using namespace std;

int main()
{
    int n, cena, pierwsza=-1, ostatnia=-1;
    cin >> n >> cena;
    int tablica[n];
    for(int i=0;i<n; i++)
    {
        cin >> tablica[i];
    }
    for(int i=0; i<n; i++)
    {
        if(tablica[i]==cena)
        {
            pierwsza=i+1;
            break;
        }
    }
    for(int i=n-1; i >= 0; i--)
    {
        if(tablica[i] == cena)
        {
            ostatnia=i+1;
            break;
        }
    }
    cout<<pierwsza<<" "<<ostatnia<<endl;

    return 0;
}
