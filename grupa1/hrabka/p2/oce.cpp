#include <iostream>

using namespace std;

int main()
{
    int n, ocena;
    cin >> n;
    int tablica[6];
    for(int i=0; i<6; i++)
    {
        tablica[i]=0;
    }
    for(int i=0; i<n; i++)
    {
        cin >> ocena;
        tablica[ocena-1]++;
    }
    for(int i=0; i<6; i++)
    {
        cout<<tablica[i]<< " ";
    }

    return 0;
}
