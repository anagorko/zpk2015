#include <iostream>
using namespace std;

int main() {
    int i,n,k;
    cin >> n ;
    i=1;
    k=1;
    if (i==0){cout<<k;}
    else{
        for(i=1; i<=n; i++){k=k*i;}
    }
            cout<<k;

}
