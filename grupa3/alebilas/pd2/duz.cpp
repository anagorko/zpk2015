#include <iostream>
using namespace std;

bool czy_rowne(string x, string y){
    if(x.length()!=y.length())
        return false;
    else{
        int len = x.length();
        for(int i=0; i<len; i++)
            if(x[i]!=y[i])
                return false;
            else
                return true;
    }
}

bool czy_rozne(string x, string y){
    if(x.length()!=y.length())
        return true;
    else{
        int len = x.length();
        for(int i=0; i<len; i++)
            if(x[i]!=y[i])
                return true;
            else
                return false;
    }
}

bool czy_mniejsze(string x, string y){
    if(x.length()<y.length())
        return true;
    else if(x.length()>y.length())
        return false;
    else{
        int len = x.length();
        for(int i=0; i<len; i++)
            if(x[i]<y[i])
                return true;
            else (x[i]>y[i])
                return false;
    }
}

bool czy_wieksze(string x, string y){
    if(x.length()>y.length())
        return true;
    else if(x.length()<y.length())
        return false;
    else{
        int len = x.length();
        for(int i=0; i<len; i++)
            if(x[i]>y[i])
                return true;
            else (x[i]<y[i])
                return false;
    }
}

bool czy_mniejsze_rowne(string x, string y){
    if(czy_wieksze(x,y))
        return false;
    else
        return true;
}

bool czy_wieksze_rowne(string x, string y){
    if(czy_mniejsze(x,y))
        return false;
    else
        return true;
}

int main(){

string x, znak, y;
bool wynik;

cin >> x >> znak >> y;

if (znak == "==")
        wynik = czy_rowne(x, y);
if (znak == "!=")
        wynik = czy_rozne(x, y);
if (znak == "<")
        wynik = czy_mniejsze(x, y);
if (znak == ">")
        wynik = czy_wieksze(x, y);
if (znak == "<=")
        wynik = czy_mniejsze_rowne(x, y);
if (znak == ">=")
        wynik = czy_wieksze_rowne(x, y);
if(wynik)
    cout << "TAK" << endl;
else
    cout << "NIE" << endl;
}
