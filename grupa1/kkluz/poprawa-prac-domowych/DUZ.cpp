#include <iostream>
#include<string>
using namespace std;

int porownaj_dlugosc(string a, string b)
{
    if (a.size()==b.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] < b[i])
                return 1;
            if (a[i] > b[i])
                return 6;
        }
            return 4;
    }
    if (a.size()>b.size())
        return 6;
    if (a.size()<b.size())
        return 1;
}

int main()
{
    string a, b, znak;
    cin >> a >> znak >> b;
    if (znak == "<"){
        if (porownaj_dlugosc(a,b)==1)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    if (znak == "<="){
        if (porownaj_dlugosc(a,b)==1 || porownaj_dlugosc(a,b)==4)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    if (znak == "!="){
        if (porownaj_dlugosc(a,b)!=4)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    if (znak == "=="){
        if (porownaj_dlugosc(a,b)==4)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    if (znak == ">="){
        if (porownaj_dlugosc(a,b)==6 || porownaj_dlugosc(a,b)==4)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
    if (znak == "<="){
        if (porownaj_dlugosc(a,b)==1 || porownaj_dlugosc(a,b)==4)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
}
