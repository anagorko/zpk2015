#include <iostream>
using namespace std;

bool porownaj(int a, int b, string c){
    bool wynik = false;
    if(c == "="){
        if(a == b)
         wynik = true;
    }
    if(c == "!="){
        if(a != b)
         wynik = true;
    }
    if(c == ">"){
        if(a > b)
         wynik = true;
    }
    if(c == "<"){
        if(a < b)
         wynik = true;
    }
    if(c == ">="){
        if(a >= b)
         wynik = true;
    }
    if(c == "<="){
        if(a <= b)
         wynik = true;
    }

return wynik;

}



int main(){
int a;
int b;
string c;
bool wynik;

cin >> a >> c >> b;

wynik = porownaj(a,b,c);
if(wynik == true)
    cout << "TAK";
else
    cout << "NIE";

return 0;
}
