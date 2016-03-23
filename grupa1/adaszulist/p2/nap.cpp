#include <iostream>
using namespace std;

int main() {
    int n;
    int i;
    cin >> n;
    int a[n];
    for (i = 0; i < n; i++)
        cin >> a[i];
    for (i = 0; i < n; i++)
        if(i % 2 == 0)
            cout << a[i] << " ";
    cout << endl;
    for (i = 0; i < n; i++)
        if(i % 2 == 1)
            cout << a[i] << " ";

    return 0;
}
