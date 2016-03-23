#include <iostream>
using namespace std;

int main () {
int wartosc;
int i;
cin >> wartosc;

while (wartosc > 0)

{
    i=wartosc%10;
    wartosc=wartosc/10;
    
    if (i!=0)
    cout << i ;
}
}
