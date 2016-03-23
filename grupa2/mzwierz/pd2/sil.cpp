#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;
    int s = 1;

    for(int i = 2; i <= n; i++)
            s *= i;

    cout << s;

}
