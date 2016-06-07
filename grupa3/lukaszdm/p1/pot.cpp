#include <iostream>
using namespace std;

int main(){
    int x,i=1;
    cin >> x;
    cout<< 1<< endl;
    if(x<=1)
        cout<<""<<endl;
    else
        while(i*2<=x){
            i*=2;
            cout <<i << endl;

        }
}


