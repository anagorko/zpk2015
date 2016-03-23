#include <iostream>
#include <string>
using namespace std;

bool wieksze (string a, string b) 
{
    int i =0, j =0, licznik =0, licznik2 =0, dl_a, dl_b;
    
            while (a[j] == '0') {
            licznik++;
            j++;
        }
        
        dl_a = a.length() - licznik;
            while (b[i] == '0') {
            licznik2++;
            i++;
        }
        dl_b = b.length() - licznik2 ;
        
        if (dl_a == 0 && dl_b == 0)
            return false;
        else {
        
            if (dl_a > dl_b)
                return true;
    
            else {
                    if (dl_a == dl_b) {
                        if (a[a.length()-1] > b[b.length()-1])
                    return true;
                        else
                    return false;
                    }
                else  // a jest mniejsze bo mniej znaków
                    return false;
            }
        }
        
}

bool wieksze_rowne (string a, string b) 
{
    int i =0, j =0, licznik = 0, licznik2 = 0, dl_a, dl_b;
    
            while (a[j] == '0') {
            licznik++;
            j++;
        }
        
        dl_a = a.length() - licznik;
            while (b[i] == '0') {
            licznik2++;
            i++;
        }
        dl_b = b.length() - licznik2 ;
        
        if (dl_a == 0 && dl_b == 0)
                return true;
        else {
        
            if (dl_a > dl_b)
                return true;
    
            else {
                if (dl_a == dl_b) {
                    if (a[a.length()-1] >= b[b.length()-1])
                        return true;
                    else
                        return false; //a mniejsze bo ostatnia cyfra mniejsza
                }
                else  // a jest mniejsze bo mniej znaków
                    return false;
            }
        }
        
}

bool rowne (string a, string b) 
{
    int i =0, j =0, licznik = 0, licznik2 = 0, dl_a, dl_b;
    
            while (a[j] == '0') {
            licznik++;
            j++;
        }
        
        dl_a = a.length() - licznik;
            while (b[i] == '0') {
            licznik2++;
            i++;
        }
        dl_b = b.length() - licznik2 ;
        
            if (dl_a == 0 && dl_b == 0)
                return true;
            else {
        
                if (dl_a > dl_b)
                    return false;
    
                else {
                    if (dl_a == dl_b) { //taka sama dlugosc
                        if (a[a.length()-1] == b[b.length()-1]) //taka sama ostatnia cyfra
                            return true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
            }
        
}


int main()
{
    string znak, a, b;

    cin >> a >> znak >> b;
        
    
    //wypisywanie
    
        if (znak == ">") {
                if (wieksze (a, b))
                    cout <<"TAK";
                else
                    cout <<"NIE";
        }
        
        else {    
            if (znak == ">=") {
                if (wieksze_rowne (a, b))
                    cout <<"TAK";
                else
                    cout <<"NIE";
            }
            
            else {
                if (znak == "==") {
                    if (rowne (a, b))
                        cout <<"TAK";
                    else
                        cout <<"NIE";
                }
                else {
                    if (znak == "<") {
                        if (!(wieksze (a, b)))
                            cout <<"TAK";
                        else
                            cout <<"NIE";
                    }
                    else {
                        if (znak == "<=") {
                            if (!(wieksze_rowne (a, b)))
                                cout <<"TAK";
                            else
                                cout <<"NIE";
                        }
                        else {
                            if (znak == "!=") {
                                if (!(rowne (a, b)))
                                    cout <<"TAK";
                                else
                                    cout <<"NIE";
                            }
                        }
                    }
                }
            }
        }
    
return 0;
}
