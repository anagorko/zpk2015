//bank.cpp
#include<iostream>
using namespace std;

class kontoKlienta
{
private:
    float stanPocz;
    int nrKonta;
public:
    void ustaw();
    void wplata(float);
    void wyplata(float);
    void saldo();
};

//funkcje składowe klasy kontoKlienta

void kontoKlienta::ustaw()
{
    cout <<"Podaj numer konta, które chcesz otworzyć:";
    cin >> nrKonta;
    cout << "Podaj adres pocztowy:";
    cin >> stanPocz;
    cout << "Utworzono konto klienta" << nrKonta << "ze stanem:" << stanPocz<< endl;
}

void kontoKlienta::wplata(float wielkWplaty)
{
    stanPocz+=wielkWplaty;
    cout << "Wpłata" << wielkWplaty << "potwierdzona" << endl;
}

void kontoKlienta::wyplata(float wielkWyplaty)
{
    if (stanPocz > wielkWyplaty)
    {
        stanPocz-=wielkWyplaty;
        cout <<"wypłata" <<wielkWyplaty <<"potwierdzona" << endl;
        return;
    }
    cout << "Stan konta nie wystracza do pobrania" << wielkWyplaty << endl;
    cout << "Wypłata" << stanPocz << "potwierdzona" << endl;
}

void kontoKlienta::saldo()
{
    cout << "Stan konta wynosi" << stanPocz << endl;
}
//funkcja maind-program

int main()
{
    kontoKlienta a1;

    a1.ustaw();
    a1.wplata(250.00);
    a1.saldo();
    a1.wyplata(500.00);
    a1.saldo();
    return(0);
}
