#include <iostream>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    int t[n];
    for (int i=0; i<n; i++)
        cin >> t[i];

    bool a=true;
    for (int i=0; i<n; i++){
            if(t[i]==x){
                cout << i+1 << " ";
                a=false;
                break;
            }
    }
    if(a)
        cout << "-1 -1" << endl;
    else {
        for (int j=n; j>=0; j--){
            if(t[j]==x){
                cout << j+1 << endl;
                break;
            }
        }
    }
}



