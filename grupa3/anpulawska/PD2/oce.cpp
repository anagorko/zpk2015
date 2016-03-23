#include <iostream>
using namespace std;

int main() {
    int n, oceny;
    cin >> n;

    int t[6];
    t[0]=0;
    t[1]=0;
    t[2]=0;
    t[3]=0;
    t[4]=0;
    t[5]=0;

    for (int i = 0; i < n; i++){
        cin >> oceny;
        t[oceny - 1]++;
    }
    for (int i = 0; i < 6; i++){
        cout << t[i] << " ";
   }
	cout << endl;
}
