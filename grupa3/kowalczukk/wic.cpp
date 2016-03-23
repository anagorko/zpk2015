#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];
    int m=t[0];
    int v=t[0];
    for (int i = 1; i < n; i++) {
        if(t[i]>m)
            m=t[i];
    }
    for (int i = 1; i < n; i++) {
        if(t[i]>v && t[i]<m)
            v=t[i];
    }
    cout << v << endl;
}
