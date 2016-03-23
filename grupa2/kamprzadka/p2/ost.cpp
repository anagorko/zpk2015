//ost
#include<iostream>
#include<math.h>
#include <iomanip>
using namespace std;


int main()
{
    unsigned int n;
    cin>>n;
    
    if(n!=0){
        if(n%4==1) cout<<2;
        if(n%4==2) cout<<4;
        if(n%4==3) cout<<8;
        if(n%4==0) cout<<6;
    }
    else cout<<1;
    
    return 0;
}
