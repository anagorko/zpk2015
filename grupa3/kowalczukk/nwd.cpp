#include <iostream>
using namespace std;

int NWD(int a, int b) {
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main(){
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];
    int y=NWD(t[0], t[1]);
    for (int i=1; i<n-1; i++) {
        int x = NWD(t[i], t[i+1]);
        if(x<y)
            y=x;
    }
    cout << y << endl;

}
