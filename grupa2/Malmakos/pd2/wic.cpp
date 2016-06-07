
#include <iostream>
using namespace std;

void zamien(int a,int b){
    int n;
    n=b;
    b=a;
    a=n;
}



int main(){

int liczba_dzieci;
int punkty;
cin>>liczba_dzieci;
int t[liczba_dzieci];
int c,d;
for(int i=0; i<liczba_dzieci;i++){
    cin>>punkty;
    t[i]=punkty;
}

for(int i=0;i<liczba_dzieci;i++){
    for(int j=i+1;j<liczba_dzieci;j++){
         if(t[i]>=t[j]){
         }else{
        c=t[i];
        t[i]=t[j];
        t[j]=c;
         }
    }
}
cout<<t[1]<<endl;
}

