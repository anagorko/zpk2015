
#include <iostream>

using namespace std;

int main()
{
    int n, najwyzsza, przednajwyzsza;
    cin >> n;
    int liczby[n];
    for(int i=0; i<n; i++)
    {
        cin >> liczby[i];
    }
    najwyzsza=liczby[0];
    for(int i=1; i<n; i++)
    {
        if(liczby[i]>najwyzsza)
        {
            najwyzsza=liczby[i];
        }
    }

    przednajwyzsza=0;
    for(int i=0; i<n; i++)
    {
        if(liczby[i]>przednajwyzsza && liczby[i]<najwyzsza)
        {
            przednajwyzsza=liczby[i];
        }
    }
    cout<<przednajwyzsza;
    return 0;
}
