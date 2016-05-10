#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
using namespace std;


int main(int argc, char** argv) {
    //sprawdzić czy istnieje x (będące liczbą naturalną) takie, że dla danych współczynników p i q spełniony jest warunek x^3 + px = q
    
    int z; //liczba zagadek
    cout<<"Podaj liczbe zagadek: ";
    cin>>z;
    cout<<endl;
    long long p[z]; //tablica współczynników p
    long long q[z]; //tablica współczynników q
    string x[z]; //tablica rozwiązań
    double tmp; //tymczasowe rozwiązanie x - jeżeli spełnia warunki zadania to zostanie przypisane do tablicy x

    for(int i=0;i<z;i++){
        cout<<"p: ";
        cin>>p[i];
        cout<<" q: ";
        cin>>q[i];
        cout<<endl;
        
        tmp=cbrtl( (q[i]/2) + sqrtl(pow((q[i]/2), 2) + pow((p[i]/3), 3))) - cbrtl( (-1)*(q[i]/2) + sqrtl(pow((q[i]/2), 2) + pow((p[i]/3), 2)));
        if(tmp >= 0 && tmp - (long long)tmp == 0){
            x[i] = to_string(tmp);
        }
        else{
            x[i] = "NIE";            
        }
    }
    
    //drukowanie rozwiązań
    
    for(int i=0;i<z;i++){
        cout<<x[i]<<endl;
    }
    return 0;
}
