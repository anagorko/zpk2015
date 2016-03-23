#include <iostream>
using namespace std;

int main() {
 int n, r;
 cin >> n >> r;
 int w = (n % 10) * 2;
 w = w + 5;
 w = w * 50;
 w = w + 1764;
 if (r >= 1920 && r <= 2007) {
 w = w - r;
 }
 cout << w << endl;

}
