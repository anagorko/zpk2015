#include <iostream>
#include <cmath>
#include<iomanip>


using namespace std;

int main() {
    int n;
    cin>>n;
    n=n-1;
    if (n==-1) cout<<1;
    else{
        if(n%4==0)cout<<2;
        if(n%4==1)cout<<4;
        if(n%4==2)cout<<8;
        if(n%4==3)cout<<6;
    }
}
