#include <iostream>
using namespace std;

int main(){
    int m;
    int n=1;
    cin >> m;

    if(n<=m){
        cout << n << endl;
        while(2*n<=m){
            cout << 2*n << endl;
            n=n*2;
            }
    }
    else{
        cout<<"nie ma takiej liczby"<<endl;
    }
}
