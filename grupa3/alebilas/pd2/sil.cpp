#include <iostream>
using namespace std;

int main(){

int n;
cin >> n;

int wynik = 1;

if(n==0){
    cout << wynik << endl;
}

else{
    for(int i=1; i<=n; i++){
        wynik = wynik*i;
    }
    cout << wynik << endl;
}
}
