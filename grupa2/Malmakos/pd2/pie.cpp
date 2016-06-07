
#include <iostream>
using namespace std;

int main(){

int n,x;
int liczba;
int pierwsza, druga;
int suma=0;

cin>>n>>x;

int akcje[n];
int wybrane[n];

for(int i=0;i<n;i++){
    cin>>liczba;
    akcje[i]=liczba;
}
int j=0;
for(int i=0;i<n;i++){
    if(akcje[i]==x){
        suma=suma+1;
              wybrane[j]=i;
              j=j+1;
    }
}
    if(suma==0){
        pierwsza=-1;
        druga=-1;
    }
    if(suma==1){
            pierwsza=wybrane[j-1]+1;
            druga=wybrane[j-1]+1;
    }

    if(suma>1){
        pierwsza=wybrane[0]+1;
        druga=wybrane[j-1]+1;
    }

cout<<pierwsza<<" "<< druga<<endl;

}




