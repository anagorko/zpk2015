#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;

    int t[a];
    for (int i=0; i<=a-1; i++)
        cin >> t[i];

    for (int i=0; i<=a-1; i+=2)
            cout << t[i] << " ";

    cout << endl;

    for (int i=1; i<=a-1; i+=2)
        cout << t[i] << " ";
}
