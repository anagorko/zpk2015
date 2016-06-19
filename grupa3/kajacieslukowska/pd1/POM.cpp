#include <iostream>
using namespace std;

int main(){
    int licznik=0;
    int a=0;
    int b=1;
    while(b!=-1){
        cin >> b;
        if (a < b){
            licznik = licznik + 1;
            a = b;
        }
    }
    cout << licznik;
}
