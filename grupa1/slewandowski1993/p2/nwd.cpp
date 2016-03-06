
#include <iostream>
using namespace std;

int NWD(int a, int b){
    while(a!=b)
       if(a>b)
           a-=b;
       else
           b-=a;
    return b;
}

int main(){

int n;
cin >> n;
int t[n];

for(int i=0;i<n;i++)
    cin >> t[i];

int wynik = NWD(t[0],t[1]);

for(int i=2;i<n;i++)
    wynik=NWD(wynik,t[i]);

cout << wynik << endl;
}
