#include <iostream>
using namespace std;

int main(){

    int a, b, k;
    cin>>a>>b>>k;
    int wynik =0;

    int bokA=a/k;
    int bokB=b/k;

    if(bokA<1 && bokB<1){
        wynik=0;
    }


    if(bokA>2 && bokB>2){

        wynik = bokA*bokB;
        wynik = wynik - (bokA-2)*(bokB-2);
    }

    else{
        wynik = bokA*bokB;
    }

    cout<<wynik;


}
