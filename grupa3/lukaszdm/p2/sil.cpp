#include <iostream>
using namespace std;

int main(){

    int n, sil=1;
    cin >> n;
    if(n==0)
        cout << 1 ;
    else{
        for(int i = 1; i<=n; i++)
            sil=sil*i;
    cout << sil ;
    }
}


