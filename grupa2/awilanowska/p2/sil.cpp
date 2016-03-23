#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int s = 1;
    for (int i = 1; i <= n; i++) {
        s = s * i;
    }

    cout << s << endl;
}
