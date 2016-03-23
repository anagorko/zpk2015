#include <iostream>
using namespace std;

// liczba wynikow (druzyn)
int n;

// zwrocenie m-tej liczby z uporzadkowanego wektora wynikow
int najwieksza_najmniejsza(int t[], int m){
    int a;

    // sortujemy wyniki od najwiekszego do najmniejszeo porownujac ze soba kolejne wyrazy wektora wynikow
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(t[i]<t[j]){
                a=t[i]; //zapisanie mniejszej liczby
                t[i]=t[j]; // podmiana obecnej wartosci na wieksza
                t[j]=a;
            }
        }
    }

return t[m-1];

}

int main(){

cin >> n;

int t[n];
int m=2;

for(int i=0; i<n; i++)
    cin >> t[i];

cout << najwieksza_najmniejsza(t,m);

}
