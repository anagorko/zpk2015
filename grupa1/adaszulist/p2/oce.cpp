#include <iostream>
using namespace std;

int main(){
int n;
cin>> n;
int lista_ocen[n];
int liczba_ocen[6]={0,0,0,0,0,0};
for(int i = 0; i < n; i++)
    cin >> lista_ocen[i];
for(int i = 0; i < n; i++){
    liczba_ocen[lista_ocen[i]-1]++;
}
for(int i = 0; i < 6; i++)
    cout << liczba_ocen[i] << " ";

return 0;
}

