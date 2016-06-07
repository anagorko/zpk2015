
#include <iostream>
using namespace std;

int main(){

int liczba;
int ilosc;
cin>>ilosc;

int a=(ilosc/2);
int z=ilosc-a;

int zuzia[z];
int antek[a];

//bool parzysta=false;//

int j=0;

for(int i=1; i<=ilosc; i++){
    if(i%2==0){
    cin>>liczba;
    antek[j]=liczba;
    //parzysta=false;//
    j=j+1;
    }
    else{
        cin>>liczba;
        zuzia[j]=liczba;
        //parzysta=true;//
    }

}


for(int i=0; i<z; i++){
    cout<<zuzia[i]<<" ";
}

cout<<endl;

for(int i=0; i<a; i++){
    cout<<antek[i]<<" ";
}







}
