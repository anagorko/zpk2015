#include <iostream>
#include <string>
using namespace std;
 
int main() 
{
    string a, b, z;
    bool mniej, wiecej, rowne, rozne, wynik;
    mniej = false;
    wiecej = false;
    rowne = false;
    rozne = false;
    wynik = false;
    int i;
    cin >> a >> z >> b;
  
        if (a==b)
        rowne = true;

        if (a.size()<b.size())
        {
            mniej = true;
            rozne = true;
        }
        else if (a.size()>b.size())
        {
            wiecej = true;
            rozne = true;
        }
        else if (a.size()==b.size())
        for (i = 0; i<=a.size(); i++)
        {
            if (a[i]<b[i] && wiecej==false)
            {
            mniej = true;
            rozne = true;
            }
            else if (a[i]>b[i] && mniej==false)
            {
            wiecej = true;
            rozne = true;
            }
        }
    
    if ((z=="==" && rowne==true) || (z=="!=" && rozne==true) || (z=="<" && mniej==true) || (z==">" && wiecej==true))
        wynik = true;
    
    if (z=="<=" && (rowne==true || mniej==true))
        wynik = true;
        
    if (z==">=" && (rowne==true || wiecej==true))
        wynik = true;


    if (wynik == true)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
