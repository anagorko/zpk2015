#include<iostream>
#include<math.h>
using namespace std;

int main(){
    int liczba;
    cin >> liczba;

    int licznik = 0;
    for(int i=2;i<=sqrt(liczba);i++){
        if(liczba%i==0)
            licznik++;
    }
    if(licznik==0)
        cout << "pierwsza" << endl;
    else
        cout << "zlozona" << endl;
}
