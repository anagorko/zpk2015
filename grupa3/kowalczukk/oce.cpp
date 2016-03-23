#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int t[n];
    for (int i=0; i<n; i++) {
        cin >> t[i];
    }
    int s[6];
    for (int i=0; i<6; i++) {
        s[i]=0;
    }
    for (int i=0; i<n; i++) {
        int x=t[i];
        s[x-1]++;
    }
    for (int i=0; i<6; i++)
        cout << s[i] << " ";
}
