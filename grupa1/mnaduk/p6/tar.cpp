    #include<iostream>
    #include<stdlib.h>
    #include<cmath>
    using namespace std;

    int main()
    {
        int liczba;
        cin >> liczba;
        long long P[liczba], Q[liczba];
        for (int i=0;i<liczba;i++)
        {
            long long odczyt;
            cin >> odczyt;
            P[i]=odczyt;
            cin >> odczyt;
            Q[i]=odczyt;
        }
        //-------------------------------------------
        for (int i=0;i<liczba;i++)
        {
            long long int p, q, wartosc;
            p = P[i];
            q = Q[i];
            int poczatek, srodek, koniec;
            poczatek = 0;
            koniec = q;
            //bool znalezione = false;
            //int licznikIteracji = 0;
            while (poczatek < koniec /*&& znalezione == false*/)
            {
                srodek = (koniec + poczatek)/2;
                wartosc = srodek*srodek*srodek + p*srodek - q;
                if(wartosc >= 0)
                    koniec = srodek;
                else
                    poczatek = srodek +1;
            }
            if (poczatek*poczatek*poczatek + p*poczatek - q == 0)
                cout << poczatek <<endl;
            else
                cout << "NIE"<<endl;
          //  cout << licznikIteracji<<endl;
        }


        return 0;
    }
