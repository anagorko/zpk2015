#include <iostream>
using namespace std;

int silnia(int a){
    int silnia;
    for(int i = 1; i <= a; i++){
        silnia *= i;
    }
    return silnia;
}
int mniejsza (int a, int b){
    if(a > b)
        return b;
    else if(a <= b)
        return a;
}


int main(){
int n, m; 
cin >> n >> m;
int ceny[n][m]; 
int ilosc_kombinacji; 
ilosc_kombinacji = silnia(n) / (2 * silnia(n-2));
int kombinacja = 0;
int koszt_rozne[ilosc_kombinacji]; 
int min_rozne; 


for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
        cin >> ceny[i][j];
    }
}

//obliczenie kosztów zrobienia zakupów w kazdych dwóch sklepach:
for(int i = 0; i < n-1; i++){
    for(int j = i+1; j < n; j++){
        koszt_rozne[kombinacja]=0;
        for(int k = 0; k < m; k++){
            koszt_rozne[kombinacja]+=mniejsza(ceny[i][k], ceny[j][k]);
        }
        kombinacja++;
    }
    kombinacja++;
}
//obliczenie kosztu minimalnego zrobienia zakupów w dwóch sklepach:
min_rozne = koszt_rozne[0];
for(int i = 1; i < ilosc_kombinacji; i++){
    min_rozne = mniejsza(min_rozne,koszt_rozne[i]);
}

cout << min_rozne;

}
