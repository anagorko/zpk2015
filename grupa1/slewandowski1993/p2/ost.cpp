#include <iostream>
using namespace std;

int main() {
    int n;
    int odp;
    cin >> n;

    if (n == 0) {odp = 1;}
    else if (n % 4 == 0) {odp = 6;}
    else if (n % 4 == 1) {odp = 2;}
    else if (n % 4 == 2) {odp = 4;}
    else if (n % 4 == 3) {odp = 8;}

   cout << odp << endl;
}
