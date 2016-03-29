#include<iostream>
using namespace std;

int main(){
    int pom, pom1;
    int wynik=0;
    cin >> pom;
    pom1=pom;
    while(pom>=0){
        cin >> pom;
            if(pom>pom1){
            pom1=pom;
            wynik++;
        }
    }
    cout << wynik << endl;
}
