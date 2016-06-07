
#include <iostream>
#include <cmath>
using namespace std;

int main(){
int liczba_sklepow;
int liczba_produktow;

cin>>liczba_sklepow;
cin>>liczba_produktow;

int tablica[liczba_sklepow][liczba_produktow];
int porownanie[liczba_sklepow][liczba_sklepow];

for(int i=0; i<liczba_sklepow;i++){
    for(int j=0; j<liczba_produktow; j++){
        cin>>tablica[i][j];
         }
     }
for(int i =0;i<liczba_sklepow-1;i++){
    for(int k=i+1; k<liczba_sklepow;k++){
                int suma=0;
                for(int j =0; j<liczba_produktow;j++){
                suma = suma + min(tablica[i][j], tablica[k][j]);
                  }
                  porownanie[i][k]=suma;
    }
}

for(int i=0; i<liczba_sklepow;i++){
    int suma_poj=0;
    for(int j = 0; j<liczba_produktow; j++){
        suma_poj=suma_poj+tablica[i][j];
    }
    porownanie[i][i]=suma_poj;

}


int minimum=porownanie[0][0];
for(int i = 0; i<liczba_sklepow;i++){
    for(int j = i; j<liczba_sklepow; j++ ){
        minimum=min(minimum, porownanie[i][j]);

            }
      }

/*for(int i=0;i<liczba_sklepow;i++){
    for(int j=i; j<liczba_sklepow;j++){
        cout<<porownanie[i][j]<< " ";
    }
    cout<<endl;
}*/

cout << minimum<< endl;

}





