#include <iostream>
using namespace std;

int main(){

int liczba;
int silnia=1;

cin>>liczba;

if(liczba==0){
    silnia =1;
    }
    else{
    for(int i=1; i<=liczba;i++){
        silnia=silnia*i;
    }
}
cout<<silnia<<endl;

}

