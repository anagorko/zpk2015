#include <iostream>;
using namespace std;

int NWD(int a, int b){

    while(a!=b){
        if(a<b)
            b=b-a;
    else
     a=a-b;
        }
    return a;
}



int main(){
int liczba_liczb;
cin>> liczba_liczb;
int t[liczba_liczb];
int liczba;

for(int i=0; i<liczba_liczb;i++){

    cin>>liczba;
    t[i]=liczba;
}

int nwd=NWD(t[0],t[1]);
for(int i=2; i<liczba_liczb;i++){
    nwd=NWD(nwd, t[i]);
    }
    cout <<nwd<<endl;
}
