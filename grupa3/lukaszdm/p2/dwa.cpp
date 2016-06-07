
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;




int minimum(int t[],int s[], int m){

int suma=0;

for(int i=0; i<m; ++i){
    if(t[i]<=s[i])
        suma+=t[i];
    else
        suma+=s[i];

}
return suma;


}

int main() {

int n, m;
cin >> n >> m;
int t[n][m];
for(int i=0;i<n;++i){
    for(int j=0; j<m; ++j)
        cin >> t[i][j];
}

int suma_min=1000000;

int suma; /*suma z dwoch analizowanych wierszy- sklep—w*/
for(int i=0; i<n-1; ++i){
    for(int j=i+1; j<n; ++j){
            int *s1=t[i];
            int *s2=t[j];
    suma=minimum(s1,s2,m);
    if(suma<suma_min)
        suma_min=suma;
    }
}


cout << suma_min;

}



