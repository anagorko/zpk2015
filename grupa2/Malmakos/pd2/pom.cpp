#include <iostream>
using namespace std;


int main(){

int a;

int suma=0;
int n=0;
cin >> a;


while(a!=-1){
     if(a>0 && a!=n){
        ++suma;
     }else {
     suma=suma;
     }
     n=a;
cin>> a;

}

cout<<suma<<endl;

}
