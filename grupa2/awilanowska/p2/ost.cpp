#include <iostream>
using namespace std;

int ostatnia_cyfra(long long n) {
    if (n == 0)
        return 1;
    else if (n % 4 == 1)
        return 2;
    else if (n % 4 == 2)
        return 4;
    else if (n % 4 == 3)
        return 8;
    else if (n % 4 == 0)
        return 6;
}

int main() {
    long long n;
    cin >> n;
    cout << ostatnia_cyfra(n) << endl;
}
