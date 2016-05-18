#include <iostream>

using namespace std;

int main()
{
    int liczbaRownan;
    cin>>liczbaRownan;

    long p[liczbaRownan];
    long q[liczbaRownan];
    for(int i=0; i<liczbaRownan; i++)
    {
        cin>>p[i];
        cin>>q[i];
    }

    for(int i=0; i<liczbaRownan; i++)
    {
        int poczatek = 1;
        int koniec = q[i];
        while (poczatek < koniec)
        {
            int srodek = (poczatek + koniec) / 2;
            if ((srodek * srodek * srodek + p[i] * srodek) >= q[i])
            {
                koniec = srodek;
            }
            else
            {
                poczatek = srodek + 1;
            }
        }
        if(poczatek*poczatek*poczatek+p[i]*poczatek==q[i])
        {
            cout <<poczatek<<endl;
        }
        else
        {
            cout<<"NIE"<<endl;
        }

    }

    return 0;
}
