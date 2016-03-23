#include <iostream>
using namespace std;

int main(){
    int n, x;
    cin >> n >> x;
    int t[n];
    int p=0, o=0;
    for(int i=0; i<n; i++)
        cin >> t[i];
    for(int i=0; i<n; i++) {
        if(t[i] == x) {
            if(p==0) {
                p=i+1;
            }
            o=i+1;
        }
    }
    if(p==0)
        cout << "-1 -1" << endl;
    else
        cout << p << " " << o << endl;
}
