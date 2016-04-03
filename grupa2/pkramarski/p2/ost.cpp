#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    if(n==0)
        cout << "1" << endl;
    else {
        int r=n%4;

        if(r==0)
            cout << "6" << endl;
        if(r==1)
            cout << "2" << endl;
        if(r==2)
            cout << "4" << endl;
        if(r==3)
            cout << "8" << endl;
        }
}
