#include <iostream>
using namespace std;

int main() {
    int A, B, K;
    cin >> A >> B >> K;
    if (A/K == 0 || B/K == 0)
        cout << 0 << endl;
    else if (A >= K && B >= K && B < 2 * K && A < 2 * K) 
        cout << "1" << endl;
    else if (A/K == 1) 
        cout << B/K << endl;
    else if (B/K == 1) 
        cout << A/K << endl;
    else
        cout << 2*(A/K - 2 + B/K)  << endl;
}
