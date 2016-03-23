#include <iostream>
using namespace std;


int main(){


    string a, znak, b, wynik;
    cin >> a >> znak >> b;

    if (a.length() > b.length())
    {
        string temporary;
        temporary.append(a.length() - b.length(), '0');
        temporary.append(b);
        b = temporary;
    }
    else if (b.length() > a.length())
    {
        string temporary;
        temporary.append(b.length() - a.length(), '0');
        temporary.append(a);
        a = temporary;
    }

    unsigned int i = 0;

    if (znak == "==")
    {
        wynik = "TAK";
        while (wynik == "TAK" && i <= a.length() - 1)
        {
            if (a[i] != b[i])
                wynik = "NIE";
            i++;
        }
    }
    else if (znak == "!=")
    {
        wynik = "NIE";
        while (wynik == "NIE" && i <= a.length() - 1)
        {
            if (a[i] != b[i])
                wynik = "TAK";
            i++;
        }
    }
    else if (znak == "<")
    {
        wynik = "NIE";
        while (wynik == "NIE" && i <= a.length() - 1)
        {
            if (a[i] < b[i])
                wynik = "TAK";
            else if (a[i] > b[i])
                break;
            i++;
        }
    }
    else if (znak == ">")
    {
        wynik = "NIE";
        while (wynik == "NIE" && i <= a.length() - 1)
        {
            if (a[i] > b[i])
                wynik = "TAK";
            else if (a[i] < b[i])
                break;
            i++;
        }
    }
    else if (znak == "<=")
    {
        wynik = "TAK";
        while (wynik == "TAK" && i <= a.length() - 1)
        {
            if (a[i] < b[i])
                break;
            else if (a[i] > b[i])
                wynik = "NIE";
            i++;
        }
    }
    else if (znak == ">=")
    {
        wynik = "TAK";
        while (wynik == "TAK" && i <= a.length() - 1)
        {
            if (a[i] > b[i])
                break;
            else if (a[i] < b[i])
                wynik = "NIE";
            i++;
        }
    }

    cout << wynik << endl;
}

