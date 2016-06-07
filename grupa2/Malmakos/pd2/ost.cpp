#include <iostream>;
#include <iomanip>;
#include <cmath>;
using namespace std;


int main(){
int liczba;

cin>>liczba;

int reszta_z_dzielenia= liczba%4;
        if(liczba ==0){
            cout<<1<<endl;
        }else if(reszta_z_dzielenia == 2){
            cout<<4<<endl;
            }else if(reszta_z_dzielenia == 3){
            cout<<8<<endl;
            }else if(reszta_z_dzielenia == 0){
            cout<<6<<endl;
            }else if(reszta_z_dzielenia == 1){
            cout<<2<<endl;
            };


}



